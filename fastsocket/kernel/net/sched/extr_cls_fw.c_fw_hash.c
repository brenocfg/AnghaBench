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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int HTSIZE ; 

__attribute__((used)) static __inline__ int fw_hash(u32 handle)
{
	if (HTSIZE == 4096)
		return ((handle >> 24) & 0xFFF) ^
		       ((handle >> 12) & 0xFFF) ^
		       (handle & 0xFFF);
	else if (HTSIZE == 2048)
		return ((handle >> 22) & 0x7FF) ^
		       ((handle >> 11) & 0x7FF) ^
		       (handle & 0x7FF);
	else if (HTSIZE == 1024)
		return ((handle >> 20) & 0x3FF) ^
		       ((handle >> 10) & 0x3FF) ^
		       (handle & 0x3FF);
	else if (HTSIZE == 512)
		return (handle >> 27) ^
		       ((handle >> 18) & 0x1FF) ^
		       ((handle >> 9) & 0x1FF) ^
		       (handle & 0x1FF);
	else if (HTSIZE == 256) {
		u8 *t = (u8 *) &handle;
		return t[0] ^ t[1] ^ t[2] ^ t[3];
	} else
		return handle & (HTSIZE - 1);
}