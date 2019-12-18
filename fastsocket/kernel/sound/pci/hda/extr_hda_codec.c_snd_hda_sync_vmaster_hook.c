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
struct hda_vmaster_mute_hook {int mute_mode; TYPE_2__* codec; int /*<<< orphan*/  (* hook ) (TYPE_2__*,int) ;int /*<<< orphan*/  sw_kctl; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {scalar_t__ shutdown; } ;

/* Variables and functions */
#define  HDA_VMUTE_FOLLOW_MASTER 128 
 int /*<<< orphan*/  snd_ctl_sync_vmaster_hook (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

void snd_hda_sync_vmaster_hook(struct hda_vmaster_mute_hook *hook)
{
	if (!hook->hook || !hook->codec)
		return;
	/* don't call vmaster hook in the destructor since it might have
	 * been already destroyed
	 */
	if (hook->codec->bus->shutdown)
		return;
	switch (hook->mute_mode) {
	case HDA_VMUTE_FOLLOW_MASTER:
		snd_ctl_sync_vmaster_hook(hook->sw_kctl);
		break;
	default:
		hook->hook(hook->codec, hook->mute_mode);
		break;
	}
}