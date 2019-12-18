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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int used; } ;
struct TYPE_3__ {TYPE_2__ buf; } ;
struct hda_codec {int /*<<< orphan*/  hash_mutex; TYPE_1__ cmd_cache; scalar_t__ cached_write; } ;
struct hda_cache_head {int /*<<< orphan*/  val; scalar_t__ dirty; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cmd_cache_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cmd_cache_nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hda_cache_head* snd_array_elem (TYPE_2__*,int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void snd_hda_codec_resume_cache(struct hda_codec *codec)
{
	int i;

	mutex_lock(&codec->hash_mutex);
	codec->cached_write = 0;
	for (i = 0; i < codec->cmd_cache.buf.used; i++) {
		struct hda_cache_head *buffer;
		u32 key;

		buffer = snd_array_elem(&codec->cmd_cache.buf, i);
		key = buffer->key;
		if (!key)
			continue;
		if (!buffer->dirty)
			continue;
		buffer->dirty = 0;
		mutex_unlock(&codec->hash_mutex);
		snd_hda_codec_write(codec, get_cmd_cache_nid(key), 0,
				    get_cmd_cache_cmd(key), buffer->val);
		mutex_lock(&codec->hash_mutex);
	}
	mutex_unlock(&codec->hash_mutex);
}