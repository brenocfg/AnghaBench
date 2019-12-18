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
typedef  unsigned char __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SSVAL (unsigned char*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int
_my_mbstowcs(__u16 *dst, const unsigned char *src, int len)
{	/* BB not a very good conversion routine - change/fix */
	int i;
	__u16 val;

	for (i = 0; i < len; i++) {
		val = *src;
		SSVAL(dst, 0, val);
		dst++;
		src++;
		if (val == 0)
			break;
	}
	return i;
}