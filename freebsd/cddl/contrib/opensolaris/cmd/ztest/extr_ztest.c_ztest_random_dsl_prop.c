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
typedef  scalar_t__ zfs_prop_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ ZFS_PROP_CHECKSUM ; 
 scalar_t__ ZIO_CHECKSUM_OFF ; 
 scalar_t__ zfs_prop_random_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_random (unsigned long long) ; 

__attribute__((used)) static uint64_t
ztest_random_dsl_prop(zfs_prop_t prop)
{
	uint64_t value;

	do {
		value = zfs_prop_random_value(prop, ztest_random(-1ULL));
	} while (prop == ZFS_PROP_CHECKSUM && value == ZIO_CHECKSUM_OFF);

	return (value);
}