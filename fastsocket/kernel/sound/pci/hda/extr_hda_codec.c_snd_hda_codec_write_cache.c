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
typedef  int /*<<< orphan*/  u32 ;
struct hda_codec {unsigned int cached_write; TYPE_1__* bus; int /*<<< orphan*/  cmd_cache; } ;
struct hda_cache_head {unsigned int val; unsigned int dirty; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_cmd_cache_key (int /*<<< orphan*/ ,unsigned int) ; 
 struct hda_cache_head* get_alloc_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 

int snd_hda_codec_write_cache(struct hda_codec *codec, hda_nid_t nid,
			      int flags, unsigned int verb, unsigned int parm)
{
	int err;
	struct hda_cache_head *c;
	u32 key;
	unsigned int cache_only;

	cache_only = codec->cached_write;
	if (!cache_only) {
		err = snd_hda_codec_write(codec, nid, flags, verb, parm);
		if (err < 0)
			return err;
	}

	/* parm may contain the verb stuff for get/set amp */
	verb = verb | (parm >> 8);
	parm &= 0xff;
	key = build_cmd_cache_key(nid, verb);
	mutex_lock(&codec->bus->cmd_mutex);
	c = get_alloc_hash(&codec->cmd_cache, key);
	if (c) {
		c->val = parm;
		c->dirty = cache_only;
	}
	mutex_unlock(&codec->bus->cmd_mutex);
	return 0;
}