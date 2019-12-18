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
 unsigned int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inl (unsigned long) ; 

void insl (unsigned long port, void *dst, unsigned long count)
{
	unsigned int l = 0, l2;
	unsigned char *p;

	p = (unsigned char *)dst;
	
	if (!count)
		return;
	
	switch (((unsigned long) dst) & 0x3)
	{
	 case 0x00:			/* Buffer 32-bit aligned */
		while (count--)
		{
			*(unsigned int *)p = cpu_to_le32(inl(port));
			p += 4;
		}
		break;
	
	 case 0x02:			/* Buffer 16-bit aligned */
		--count;
		
		l = cpu_to_le32(inl(port));
		*(unsigned short *)p = l >> 16;
		p += 2;
		
		while (count--)
		{
			l2 = cpu_to_le32(inl(port));
			*(unsigned int *)p = (l & 0xffff) << 16 | (l2 >> 16);
			p += 4;
			l = l2;
		}
		*(unsigned short *)p = l & 0xffff;
		break;
	 case 0x01:			/* Buffer 8-bit aligned */
		--count;
		
		l = cpu_to_le32(inl(port));
		*(unsigned char *)p = l >> 24;
		p++;
		*(unsigned short *)p = (l >> 8) & 0xffff;
		p += 2;
		while (count--)
		{
			l2 = cpu_to_le32(inl(port));
			*(unsigned int *)p = (l & 0xff) << 24 | (l2 >> 8);
			p += 4;
			l = l2;
		}
		*p = l & 0xff;
		break;
	 case 0x03:			/* Buffer 8-bit aligned */
		--count;
		
		l = cpu_to_le32(inl(port));
		*p = l >> 24;
		p++;
		while (count--)
		{
			l2 = cpu_to_le32(inl(port));
			*(unsigned int *)p = (l & 0xffffff) << 8 | l2 >> 24;
			p += 4;
			l = l2;
		}
		*(unsigned short *)p = (l >> 8) & 0xffff;
		p += 2;
		*p = l & 0xff;
		break;
	}
}