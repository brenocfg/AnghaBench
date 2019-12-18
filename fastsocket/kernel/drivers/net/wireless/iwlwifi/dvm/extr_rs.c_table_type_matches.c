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
struct iwl_scale_tbl_info {scalar_t__ lq_type; scalar_t__ ant_type; scalar_t__ is_SGI; } ;

/* Variables and functions */

__attribute__((used)) static bool table_type_matches(struct iwl_scale_tbl_info *a,
			       struct iwl_scale_tbl_info *b)
{
	return (a->lq_type == b->lq_type) && (a->ant_type == b->ant_type) &&
		(a->is_SGI == b->is_SGI);
}