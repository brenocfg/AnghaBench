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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 

void crypto4xx_memcpy_le(unsigned int *dst,
			 const unsigned char *buf,
			 int len)
{
	u8 *tmp;
	for (; len >= 4; buf += 4, len -= 4)
		*dst++ = cpu_to_le32(*(unsigned int *) buf);

	tmp = (u8 *)dst;
	switch (len) {
	case 3:
		*tmp++ = 0;
		*tmp++ = *(buf+2);
		*tmp++ = *(buf+1);
		*tmp++ = *buf;
		break;
	case 2:
		*tmp++ = 0;
		*tmp++ = 0;
		*tmp++ = *(buf+1);
		*tmp++ = *buf;
		break;
	case 1:
		*tmp++ = 0;
		*tmp++ = 0;
		*tmp++ = 0;
		*tmp++ = *buf;
		break;
	default:
		break;
	}
}