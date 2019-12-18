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
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/ * hextable ; 

__attribute__((used)) static __u8 *add_checksum(__u8 * buffer, __u8 * end)
{
	__u16 sum = 0;
	__u8 *p = buffer;
	while (p < end)
		sum += *p++;
	end[3] = hextable[sum & 0xF];
	sum >>= 4;
	end[2] = hextable[sum & 0xF];
	sum >>= 4;
	end[1] = hextable[sum & 0xF];
	sum >>= 4;
	end[0] = hextable[sum & 0xF];
	return (end + 4);
}