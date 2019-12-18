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
struct se_lun {TYPE_1__* lun_sep; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  sep_tg_pt_secondary_offline; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

ssize_t core_alua_show_offline_bit(struct se_lun *lun, char *page)
{
	if (!lun->lun_sep)
		return -ENODEV;

	return sprintf(page, "%d\n",
		atomic_read(&lun->lun_sep->sep_tg_pt_secondary_offline));
}