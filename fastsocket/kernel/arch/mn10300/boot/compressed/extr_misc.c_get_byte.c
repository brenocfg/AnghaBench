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
 unsigned char fill_inbuf () ; 
 unsigned char* inbuf ; 
 scalar_t__ inptr ; 
 scalar_t__ insize ; 
 int /*<<< orphan*/  kputs (char*) ; 

__attribute__((used)) static inline unsigned char get_byte(void)
{
	unsigned char ch = inptr < insize ? inbuf[inptr++] : fill_inbuf();

#if 0
	char hex[3];
	hex[0] = ((ch & 0x0f) > 9) ?
		((ch & 0x0f) + 'A' - 0xa) : ((ch & 0x0f) + '0');
	hex[1] = ((ch >> 4) > 9) ?
		((ch >> 4) + 'A' - 0xa) : ((ch >> 4) + '0');
	hex[2] = 0;
	kputs(hex);
#endif
	return ch;
}