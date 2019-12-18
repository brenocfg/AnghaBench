#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* d_size; void* d_stream_first_sector; void* d_modified; void* d_created; void* d_flags; void** d_storage_uuid; void* d_storage; void* d_right_child; void* d_left_child; int /*<<< orphan*/  d_namelen; } ;
typedef  TYPE_1__ cdf_directory_t ;

/* Variables and functions */
 void* CAST (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  CDF_TOLE2 (int /*<<< orphan*/ ) ; 
 void* CDF_TOLE4 (void*) ; 
 void* CDF_TOLE8 (void*) ; 
 int /*<<< orphan*/  uint32_t ; 
 int /*<<< orphan*/  uint64_t ; 

void
cdf_swap_dir(cdf_directory_t *d)
{
	d->d_namelen = CDF_TOLE2(d->d_namelen);
	d->d_left_child = CDF_TOLE4(CAST(uint32_t, d->d_left_child));
	d->d_right_child = CDF_TOLE4(CAST(uint32_t, d->d_right_child));
	d->d_storage = CDF_TOLE4(CAST(uint32_t, d->d_storage));
	d->d_storage_uuid[0] = CDF_TOLE8(d->d_storage_uuid[0]);
	d->d_storage_uuid[1] = CDF_TOLE8(d->d_storage_uuid[1]);
	d->d_flags = CDF_TOLE4(d->d_flags);
	d->d_created = CDF_TOLE8(CAST(uint64_t, d->d_created));
	d->d_modified = CDF_TOLE8(CAST(uint64_t, d->d_modified));
	d->d_stream_first_sector = CDF_TOLE4(
	    CAST(uint32_t, d->d_stream_first_sector));
	d->d_size = CDF_TOLE4(d->d_size);
}