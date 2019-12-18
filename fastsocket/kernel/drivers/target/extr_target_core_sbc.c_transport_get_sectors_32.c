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
typedef  scalar_t__ u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 transport_get_sectors_32(unsigned char *cdb)
{
	return (u32)(cdb[28] << 24) + (cdb[29] << 16) +
		    (cdb[30] << 8) + cdb[31];

}