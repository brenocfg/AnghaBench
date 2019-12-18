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
struct seq_file {struct ap_data* private; } ;
struct ap_data {int /*<<< orphan*/  sta_list; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* seq_list_next (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *prism2_ap_proc_next(struct seq_file *m, void *v, loff_t *_pos)
{
	struct ap_data *ap = m->private;
	return seq_list_next(v, &ap->sta_list, _pos);
}