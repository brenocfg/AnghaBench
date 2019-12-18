#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct nlm_file {TYPE_3__* f_file; } ;
struct TYPE_5__ {TYPE_1__* mnt; } ;
struct TYPE_6__ {TYPE_2__ f_path; } ;
struct TYPE_4__ {struct super_block* mnt_sb; } ;

/* Variables and functions */

__attribute__((used)) static int
nlmsvc_match_sb(void *datap, struct nlm_file *file)
{
	struct super_block *sb = datap;

	return sb == file->f_file->f_path.mnt->mnt_sb;
}