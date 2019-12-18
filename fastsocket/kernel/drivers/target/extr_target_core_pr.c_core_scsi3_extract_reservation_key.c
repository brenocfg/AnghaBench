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

__attribute__((used)) static unsigned long long core_scsi3_extract_reservation_key(unsigned char *cdb)
{
	unsigned int __v1, __v2;

	__v1 = (cdb[0] << 24) | (cdb[1] << 16) | (cdb[2] << 8) | cdb[3];
	__v2 = (cdb[4] << 24) | (cdb[5] << 16) | (cdb[6] << 8) | cdb[7];

	return ((unsigned long long)__v2) | (unsigned long long)__v1 << 32;
}