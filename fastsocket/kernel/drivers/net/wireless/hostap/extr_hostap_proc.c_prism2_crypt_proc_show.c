#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct seq_file {TYPE_4__* private; } ;
struct TYPE_7__ {TYPE_2__** crypt; int /*<<< orphan*/  tx_keyidx; } ;
struct TYPE_8__ {TYPE_3__ crypt_info; } ;
typedef  TYPE_4__ local_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* print_stats ) (struct seq_file*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int WEP_KEYS ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct seq_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prism2_crypt_proc_show(struct seq_file *m, void *v)
{
	local_info_t *local = m->private;
	int i;

	seq_printf(m, "tx_keyidx=%d\n", local->crypt_info.tx_keyidx);
	for (i = 0; i < WEP_KEYS; i++) {
		if (local->crypt_info.crypt[i] &&
		    local->crypt_info.crypt[i]->ops &&
		    local->crypt_info.crypt[i]->ops->print_stats) {
			local->crypt_info.crypt[i]->ops->print_stats(
				m, local->crypt_info.crypt[i]->priv);
		}
	}
	return 0;
}