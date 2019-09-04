#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mzn_name; } ;
typedef  TYPE_1__ mach_zone_name_t ;
struct TYPE_6__ {int /*<<< orphan*/  mzi_count; int /*<<< orphan*/  mzi_cur_size; } ;
typedef  TYPE_2__ mach_zone_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_LOG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_zone_info(mach_zone_name_t *zn, mach_zone_info_t *zi)
{
	T_LOG("ZONE NAME: %-35sSIZE: %-25lluELEMENTS: %llu",
			zn->mzn_name, zi->mzi_cur_size, zi->mzi_count);
}