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
struct snd_cs46xx {int /*<<< orphan*/  spos_mutex; struct dsp_spos_instance* dsp_spos_instance; } ;
struct TYPE_5__ {int /*<<< orphan*/  symbols; } ;
struct TYPE_4__ {struct dsp_spos_instance* data; } ;
struct dsp_spos_instance {int nscb; struct dsp_spos_instance* modules; TYPE_2__ symbol_table; TYPE_1__ code; TYPE_3__* scbs; } ;
struct TYPE_6__ {scalar_t__ deleted; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs46xx_dsp_proc_free_scb_desc (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct dsp_spos_instance*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void  cs46xx_dsp_spos_destroy (struct snd_cs46xx * chip)
{
	int i;
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if (snd_BUG_ON(!ins))
		return;

	mutex_lock(&chip->spos_mutex);
	for (i = 0; i < ins->nscb; ++i) {
		if (ins->scbs[i].deleted) continue;

		cs46xx_dsp_proc_free_scb_desc ( (ins->scbs + i) );
	}

	kfree(ins->code.data);
	vfree(ins->symbol_table.symbols);
	kfree(ins->modules);
	kfree(ins);
	mutex_unlock(&chip->spos_mutex);
}