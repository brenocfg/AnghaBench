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
struct TYPE_3__ {int /*<<< orphan*/  hp_outs; } ;
struct TYPE_4__ {TYPE_1__ autocfg; } ;
struct via_spec {scalar_t__ codec_type; int hp_work_active; TYPE_2__ gen; } ;
struct hda_codec {scalar_t__ jackpoll_interval; int /*<<< orphan*/  jackpoll_work; struct via_spec* spec; } ;

/* Variables and functions */
 scalar_t__ VT1708 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void vt1708_stop_hp_work(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;
	if (spec->codec_type != VT1708 || !spec->gen.autocfg.hp_outs)
		return;
	if (spec->hp_work_active) {
		snd_hda_codec_write(codec, 0x1, 0, 0xf81, 1);
		cancel_delayed_work_sync(&codec->jackpoll_work);
		spec->hp_work_active = false;
		codec->jackpoll_interval = 0;
	}
}