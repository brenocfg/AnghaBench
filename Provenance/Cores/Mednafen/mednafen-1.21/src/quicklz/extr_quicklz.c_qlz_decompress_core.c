#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 unsigned int fast_read (unsigned char const*,int) ; 
 unsigned int fast_read_safe (unsigned char const*,int,unsigned char const*) ; 
 size_t hash_func (unsigned int) ; 
 int /*<<< orphan*/  memcpy_up (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned char,unsigned int) ; 

size_t qlz_decompress_core(const unsigned char *source, void *destination, size_t size, size_t source_size, unsigned char *first_valid, const unsigned char *hashtable[])
{
	const unsigned char *source_c = (const unsigned char*)source;
	unsigned char *destination_c = (unsigned char*)destination;
	const unsigned char *src = source_c;
	unsigned char *dst = destination_c;
	const unsigned char* last_byte_successor = destination_c + size;
	unsigned int cword_val = 1;
	const unsigned int bitlut[16] = {4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0};
	const unsigned char *guaranteed_uncompressed = last_byte_successor - 4;
	unsigned char *last_hashed = destination_c + 3;

	first_valid = first_valid;
	last_hashed = last_hashed;
	hashtable = hashtable;
		
	// prevent spurious memory read on a source with size < 4
	if (dst >= guaranteed_uncompressed)
	{
		src += 4;
		while(dst < last_byte_successor)
		{
			*dst = *src;
			dst++;
			src++;
		}

		return (unsigned int)(dst - destination_c);
	}


	for(;;) 
	{
		unsigned int fetch;

		if (cword_val == 1)
		{
			// fetch control word
			cword_val = fast_read_safe(src, 4, source_c + source_size) | (1U << 31);
			src += 4;
		}
		
		fetch = fast_read_safe(src, 4, source_c + source_size);

	 	// check if we must decode lz match
		if ((cword_val & 1) == 1)
		{
			unsigned int matchlen;

#if(QLZ_COMPRESSION_LEVEL == 0)
			unsigned int hash;
			const unsigned char *offset2;

			cword_val = cword_val >> 1;			

			if((fetch & 0xf) != 15)
			{
				hash = (fetch >> 4) & 0xfff;
				offset2 = hashtable[hash];

				if((fetch & 0xf) != 0)
				{
					matchlen = (fetch & 0xf);
					src += 2;			
				}
				else if((fetch & 0x00ff0000) != 0)
				{
					matchlen = *(src + 2);
					src += 3;							
				}
				else
				{
					matchlen = fast_read(src + 3, 4);
					src += 7;
				}
				memcpy_up(dst, offset2, matchlen);
				while(last_hashed < dst)
				{
					last_hashed++;
					hashtable[hash_func(fast_read(last_hashed, 4))] = last_hashed;
				}				
				dst += matchlen;
				last_hashed = dst - 1;				
			}
				
#else		
			unsigned int offset;
			cword_val = cword_val >> 1;			

			if ((fetch & 3) == 0)
			{
				offset = (fetch & 0xff) >> 2;
#ifdef memory_safe	
				if (3 > (unsigned int)(guaranteed_uncompressed - dst) || offset > (unsigned int)(dst - first_valid))
					return 0;
#endif
				memcpy_up(dst, dst - offset, 3);
				dst += 3;
				src++;
			}
			else if ((fetch & 2) == 0)
			{
				offset = (fetch & 0xffff) >> 2;
#ifdef memory_safe	
				if (3 > (unsigned int)(guaranteed_uncompressed - dst) || offset > (unsigned int)(dst - first_valid)) 
					return 0;
#endif
				memcpy_up(dst, dst - offset, 3);
				dst += 3;
				src += 2;
			}
			else if ((fetch & 1) == 0)
			{
				offset = (fetch & 0xffff) >> 6;
				matchlen = ((fetch >> 2) & 15) + 3;
#ifdef memory_safe	
				if (matchlen > (unsigned int)(guaranteed_uncompressed - dst) || offset > (unsigned int)(dst - first_valid)) 
					return 0;
#endif
				memcpy_up(dst, dst - offset, matchlen);
				src += 2;
				dst += matchlen;
			}
			else if ((fetch & 4) == 0)
			{
				offset = (fetch & 0xffffff) >> 8;
				matchlen = ((fetch >> 3) & 31) + 3;
#ifdef memory_safe	
				if (matchlen > (unsigned int)(guaranteed_uncompressed - dst) || offset > (unsigned int)(dst - first_valid)) 
					return 0;
#endif
				memcpy_up(dst, dst - offset, matchlen);
				src += 3;
				dst += matchlen;
			}
			else if ((fetch & 8) == 0)
			{
				offset = (fetch >> 15);
				if (offset != 0)
				{
					matchlen = ((fetch >> 4) & 2047) + 3;
					src += 4;
				}
				else
				{
					matchlen = fast_read_safe(src + 4, 4, source_c + source_size);
					offset = fast_read_safe(src + 8, 4, source_c + source_size);
					src += 12;
				}
#ifdef memory_safe	
				if (matchlen > (unsigned int)(guaranteed_uncompressed - dst) || offset > (unsigned int)(dst - first_valid)) 
					return 0;
#endif
				memcpy_up(dst, dst - offset, matchlen);
				dst += matchlen;
			}
#endif
			else
			{
				// decode rle sequence
				unsigned char rle_char;
				rle_char = (unsigned char)(fetch >> 16);
				matchlen = ((fetch >> 4) & 0xfff);

				if(matchlen != 0)
					src += 3;
				else
				{
					matchlen = fast_read_safe(src + 3, 4, source_c + source_size);
					src += 7;
				}

#ifdef memory_safe	
				if(matchlen > (unsigned int)(guaranteed_uncompressed - dst)) 
					return 0;
#endif
				memset(dst, rle_char, matchlen);

#if(QLZ_COMPRESSION_LEVEL == 0)
				while(last_hashed < dst - 1)
				{
					last_hashed++;
					hashtable[hash_func(fast_read(last_hashed, 4))] = last_hashed;
				}				
				last_hashed = dst - 1 + matchlen;
#endif
				dst += matchlen; 
			}
		}
		else
		{
			// decode literal
#ifdef memory_safe 
			if (4 > destination_c + size - dst || src > source_c + source_size + 4) 
				return 0;
#endif
			memcpy_up(dst, src, 4);

			dst += bitlut[cword_val & 0xf];
			src += bitlut[cword_val & 0xf];
			cword_val = cword_val >> (bitlut[cword_val & 0xf]);

#if(QLZ_COMPRESSION_LEVEL == 0)
			while(last_hashed < dst - 3)
			{
				last_hashed++;
				hashtable[hash_func(fast_read(last_hashed, 4))] = last_hashed;
			}
#endif
			if (dst >= guaranteed_uncompressed)
			{
				// decode last literals and exit				
				while(dst < last_byte_successor)
				{
					if (cword_val == 1)
					{
						src += 4;
						cword_val = 1U << 31;
					}
					if (1 > destination_c + size - dst)
						return 0;

					*dst = *src;
					dst++;
					src++;
					cword_val = cword_val >> 1;
				}

#if(QLZ_COMPRESSION_LEVEL == 0)
				while(last_hashed < last_byte_successor - 4)
				{
					last_hashed++;
					hashtable[hash_func(fast_read(last_hashed, 4))] = last_hashed;
				}
#endif
				if((src - 1) - source_c > 8) // 8 bytes comp. size excessive len is ok
					return 0;
				else if(dst - destination_c - size == 0)
					return size;
				else
					return 0;
			}
		}
	}
}