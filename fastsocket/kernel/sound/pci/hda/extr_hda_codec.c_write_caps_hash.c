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
struct hda_codec {int /*<<< orphan*/  hash_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct hda_amp_info {unsigned int amp_caps; TYPE_1__ head; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INFO_AMP_CAPS ; 
 struct hda_amp_info* get_alloc_amp_hash (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_caps_hash(struct hda_codec *codec, u32 key, unsigned int val)
{
	struct hda_amp_info *info;

	mutex_lock(&codec->hash_mutex);
	info = get_alloc_amp_hash(codec, key);
	if (!info) {
		mutex_unlock(&codec->hash_mutex);
		return -EINVAL;
	}
	info->amp_caps = val;
	info->head.val |= INFO_AMP_CAPS;
	mutex_unlock(&codec->hash_mutex);
	return 0;
}