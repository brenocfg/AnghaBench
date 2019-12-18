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
typedef  int u32 ;
struct TYPE_6__ {int used; } ;
struct TYPE_4__ {TYPE_3__ buf; } ;
struct hda_codec {int /*<<< orphan*/  hash_mutex; TYPE_1__ amp_cache; scalar_t__ cached_write; } ;
struct TYPE_5__ {int key; int val; scalar_t__ dirty; } ;
struct hda_amp_info {int /*<<< orphan*/ * vol; int /*<<< orphan*/  amp_caps; TYPE_2__ head; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int INFO_AMP_VOL (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_vol_mute (struct hda_codec*,int /*<<< orphan*/ ,int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 struct hda_amp_info* snd_array_elem (TYPE_3__*,int) ; 

void snd_hda_codec_resume_amp(struct hda_codec *codec)
{
	int i;

	mutex_lock(&codec->hash_mutex);
	codec->cached_write = 0;
	for (i = 0; i < codec->amp_cache.buf.used; i++) {
		struct hda_amp_info *buffer;
		u32 key;
		hda_nid_t nid;
		unsigned int idx, dir, ch;
		struct hda_amp_info info;

		buffer = snd_array_elem(&codec->amp_cache.buf, i);
		if (!buffer->head.dirty)
			continue;
		buffer->head.dirty = 0;
		info = *buffer;
		key = info.head.key;
		if (!key)
			continue;
		nid = key & 0xff;
		idx = (key >> 16) & 0xff;
		dir = (key >> 24) & 0xff;
		for (ch = 0; ch < 2; ch++) {
			if (!(info.head.val & INFO_AMP_VOL(ch)))
				continue;
			mutex_unlock(&codec->hash_mutex);
			put_vol_mute(codec, info.amp_caps, nid, ch, dir, idx,
				     info.vol[ch]);
			mutex_lock(&codec->hash_mutex);
		}
	}
	mutex_unlock(&codec->hash_mutex);
}