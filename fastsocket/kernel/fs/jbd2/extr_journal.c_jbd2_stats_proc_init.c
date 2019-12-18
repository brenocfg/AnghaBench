#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ j_proc_entry; int /*<<< orphan*/  j_devname; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  jbd2_seq_info_fops ; 
 int /*<<< orphan*/  proc_create_data (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  proc_jbd2_stats ; 
 scalar_t__ proc_mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jbd2_stats_proc_init(journal_t *journal)
{
	journal->j_proc_entry = proc_mkdir(journal->j_devname, proc_jbd2_stats);
	if (journal->j_proc_entry) {
		proc_create_data("info", S_IRUGO, journal->j_proc_entry,
				 &jbd2_seq_info_fops, journal);
	}
}