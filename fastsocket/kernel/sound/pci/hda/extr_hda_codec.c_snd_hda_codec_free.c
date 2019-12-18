#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (struct hda_codec*) ;} ;
struct hda_codec {size_t addr; struct hda_codec* wcaps; struct hda_codec* modelname; struct hda_codec* chip_name; struct hda_codec* vendor_name; int /*<<< orphan*/  cmd_cache; int /*<<< orphan*/  amp_cache; int /*<<< orphan*/  owner; TYPE_2__* bus; int /*<<< orphan*/  pm_down_notified; TYPE_1__ patch_ops; int /*<<< orphan*/  spdif_out; int /*<<< orphan*/  cvt_setups; int /*<<< orphan*/  nids; int /*<<< orphan*/  mixers; int /*<<< orphan*/  list; int /*<<< orphan*/  power_work; int /*<<< orphan*/  jackpoll_work; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** caddr_tbl; int /*<<< orphan*/  workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_hda_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_init_pincfgs (struct hda_codec*) ; 
 int /*<<< orphan*/  hda_call_pm_notify (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kfree (struct hda_codec*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_conn_list (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_array_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_jack_tbl_clear (struct hda_codec*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*) ; 

__attribute__((used)) static void snd_hda_codec_free(struct hda_codec *codec)
{
	if (!codec)
		return;
	cancel_delayed_work_sync(&codec->jackpoll_work);
	snd_hda_jack_tbl_clear(codec);
	free_init_pincfgs(codec);
#ifdef CONFIG_PM
	cancel_delayed_work(&codec->power_work);
	flush_workqueue(codec->bus->workq);
#endif
	list_del(&codec->list);
	snd_array_free(&codec->mixers);
	snd_array_free(&codec->nids);
	snd_array_free(&codec->cvt_setups);
	snd_array_free(&codec->spdif_out);
	remove_conn_list(codec);
	codec->bus->caddr_tbl[codec->addr] = NULL;
	if (codec->patch_ops.free)
		codec->patch_ops.free(codec);
#ifdef CONFIG_PM
	if (!codec->pm_down_notified) /* cancel leftover refcounts */
		hda_call_pm_notify(codec->bus, false);
#endif
	module_put(codec->owner);
	free_hda_cache(&codec->amp_cache);
	free_hda_cache(&codec->cmd_cache);
	kfree(codec->vendor_name);
	kfree(codec->chip_name);
	kfree(codec->modelname);
	kfree(codec->wcaps);
	kfree(codec);
}