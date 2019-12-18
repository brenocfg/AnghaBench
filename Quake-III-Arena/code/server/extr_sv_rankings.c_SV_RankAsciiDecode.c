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
typedef  int /*<<< orphan*/  s_inverse_encoding ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 size_t* s_ascii_encoding ; 

__attribute__((used)) static int SV_RankAsciiDecode( unsigned char* dest, const char* src, 
	int src_len )
{
	static unsigned char	s_inverse_encoding[256];
	static char				s_init = 0;
	
	unsigned char	bin[3];
	unsigned char	txt[4];
	int				dest_len = 0;
	int				i;
	int				j;
	int				num_bytes;
	
	assert( dest != NULL );
	assert( src != NULL );

	if( !s_init )
	{
		// initialize lookup table for decoding
		memset( s_inverse_encoding, 255, sizeof(s_inverse_encoding) );
		for( i = 0; i < 64; i++ )
		{
			s_inverse_encoding[s_ascii_encoding[i]] = i;
		}
		s_init = 1;
	}
	
	for( i = 0; i < src_len; i += 4 )
	{
		// read four characters of input, decode them to 6-bit values
		for( j = 0; j < 4; j++ )
		{
			txt[j] = (i + j < src_len) ? s_inverse_encoding[src[i + j]] : 0;
			if (txt[j] == 255)
			{
				return 0; // invalid input character
			}
		}
		
		// get three bytes from four 6-bit values
		bin[0] = (txt[0] << 2) | (txt[1] >> 4);
		bin[1] = (txt[1] << 4) | (txt[2] >> 2);
		bin[2] = (txt[2] << 6) | txt[3];

		// store binary data
		num_bytes = (i + 3 < src_len) ? 3 : ((src_len - i) * 3) / 4;
		for( j = 0; j < num_bytes; j++ )
		{
			dest[dest_len++] = bin[j];
		}
	}

	return dest_len;
}