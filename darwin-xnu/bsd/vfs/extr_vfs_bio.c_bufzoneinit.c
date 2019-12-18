#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct buf {int dummy; } ;
struct TYPE_2__ {scalar_t__ mz_size; int mz_max; char* mz_name; void* mz_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  Z_CALLERACCT ; 
 void* buf_hdr_zone ; 
 TYPE_1__* meta_zones ; 
 void* zinit (int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zone_change (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bufzoneinit(void)
{
	int i;

	for (i = 0; meta_zones[i].mz_size != 0; i++) {
		meta_zones[i].mz_zone = 
				zinit(meta_zones[i].mz_size,
					meta_zones[i].mz_max,
					PAGE_SIZE,
					meta_zones[i].mz_name);
		zone_change(meta_zones[i].mz_zone, Z_CALLERACCT, FALSE);
	}
	buf_hdr_zone = zinit(sizeof(struct buf), 32, PAGE_SIZE, "buf headers");
	zone_change(buf_hdr_zone, Z_CALLERACCT, FALSE);
}