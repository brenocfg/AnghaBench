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
typedef  int /*<<< orphan*/  zone_t ;
struct TYPE_2__ {size_t mz_size; int /*<<< orphan*/  mz_zone; } ;

/* Variables and functions */
 size_t MAXMETA ; 
 size_t MINMETA ; 
 TYPE_1__* meta_zones ; 
 int /*<<< orphan*/  panic (char*,size_t) ; 

__attribute__((used)) static __inline__ zone_t
getbufzone(size_t size)
{
	int i;

	if ((size % 512) || (size < MINMETA) || (size > MAXMETA))
		panic("getbufzone: incorect size = %lu", size);

	for (i = 0; meta_zones[i].mz_size != 0; i++) {
		if (meta_zones[i].mz_size >= size)
			break;
	}

	return (meta_zones[i].mz_zone);
}