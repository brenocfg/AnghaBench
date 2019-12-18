#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t nlevels; TYPE_1__* levels; } ;
typedef  TYPE_2__ bitmap_info_t ;
struct TYPE_4__ {size_t group_offset; } ;

/* Variables and functions */
 size_t LG_SIZEOF_BITMAP ; 

size_t
bitmap_info_ngroups(const bitmap_info_t *binfo)
{

	return (binfo->levels[binfo->nlevels].group_offset << LG_SIZEOF_BITMAP);
}