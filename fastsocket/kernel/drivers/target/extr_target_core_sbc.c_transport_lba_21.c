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
typedef  unsigned char u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 transport_lba_21(unsigned char *cdb)
{
	return ((cdb[1] & 0x1f) << 16) | (cdb[2] << 8) | cdb[3];
}