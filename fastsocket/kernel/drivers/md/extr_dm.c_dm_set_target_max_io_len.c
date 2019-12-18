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
typedef  scalar_t__ uint32_t ;
struct dm_target {char* error; scalar_t__ split_io; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,unsigned long long,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ UINT_MAX ; 

int dm_set_target_max_io_len(struct dm_target *ti, sector_t len)
{
	if (len > UINT_MAX) {
		DMERR("Specified maximum size of target IO (%llu) exceeds limit (%u)",
		      (unsigned long long)len, UINT_MAX);
		ti->error = "Maximum size of target IO is too large";
		return -EINVAL;
	}

	ti->split_io = (uint32_t) len;

	return 0;
}