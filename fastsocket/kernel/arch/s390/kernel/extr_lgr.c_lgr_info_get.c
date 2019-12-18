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
struct lgr_info {int level; int /*<<< orphan*/  stfle_fac_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOSYS ; 
 int /*<<< orphan*/  lgr_stsi_1_1_1 (struct lgr_info*) ; 
 int /*<<< orphan*/  lgr_stsi_2_2_2 (struct lgr_info*) ; 
 int /*<<< orphan*/  lgr_stsi_3_2_2 (struct lgr_info*) ; 
 int /*<<< orphan*/  memset (struct lgr_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stfle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stsi_0 () ; 

__attribute__((used)) static void lgr_info_get(struct lgr_info *lgr_info)
{
	memset(lgr_info, 0, sizeof(*lgr_info));
	stfle(lgr_info->stfle_fac_list, ARRAY_SIZE(lgr_info->stfle_fac_list));
	lgr_info->level = stsi_0();
	if (lgr_info->level == -ENOSYS)
		return;
	if (lgr_info->level >= 1)
		lgr_stsi_1_1_1(lgr_info);
	if (lgr_info->level >= 2)
		lgr_stsi_2_2_2(lgr_info);
	if (lgr_info->level >= 3)
		lgr_stsi_3_2_2(lgr_info);
}