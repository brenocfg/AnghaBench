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
struct hda_codec {unsigned int cached_write; int /*<<< orphan*/  hash_mutex; } ;
struct TYPE_2__ {unsigned int dirty; } ;
struct hda_amp_info {int* vol; unsigned int amp_caps; TYPE_1__ head; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_vol_mute (struct hda_codec*,unsigned int,int /*<<< orphan*/ ,int,int,int,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct hda_amp_info* update_amp_hash (struct hda_codec*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int codec_amp_update(struct hda_codec *codec, hda_nid_t nid, int ch,
			    int direction, int idx, int mask, int val,
			    bool init_only)
{
	struct hda_amp_info *info;
	unsigned int caps;
	unsigned int cache_only;

	if (snd_BUG_ON(mask & ~0xff))
		mask &= 0xff;
	val &= mask;

	mutex_lock(&codec->hash_mutex);
	info = update_amp_hash(codec, nid, ch, direction, idx, init_only);
	if (!info) {
		mutex_unlock(&codec->hash_mutex);
		return 0;
	}
	val |= info->vol[ch] & ~mask;
	if (info->vol[ch] == val) {
		mutex_unlock(&codec->hash_mutex);
		return 0;
	}
	info->vol[ch] = val;
	cache_only = info->head.dirty = codec->cached_write;
	caps = info->amp_caps;
	mutex_unlock(&codec->hash_mutex);
	if (!cache_only)
		put_vol_mute(codec, caps, nid, ch, direction, idx, val);
	return 1;
}