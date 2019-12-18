#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct transfer_info {int tag; } ;
struct onyx {int /*<<< orphan*/  mutex; } ;
struct codec_info_item {struct onyx* codec_data; } ;

/* Variables and functions */
 int ONYX_MUTE_LEFT ; 
 int ONYX_MUTE_RIGHT ; 
 int /*<<< orphan*/  ONYX_REG_DAC_CONTROL ; 
 int /*<<< orphan*/  ONYX_REG_DIG_INFO4 ; 
 int ONYX_SPDIF_ENABLE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onyx_read_register (struct onyx*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int onyx_usable(struct codec_info_item *cii,
		       struct transfer_info *ti,
		       struct transfer_info *out)
{
	u8 v;
	struct onyx *onyx = cii->codec_data;
	int spdif_enabled, analog_enabled;

	mutex_lock(&onyx->mutex);
	onyx_read_register(onyx, ONYX_REG_DIG_INFO4, &v);
	spdif_enabled = !!(v & ONYX_SPDIF_ENABLE);
	onyx_read_register(onyx, ONYX_REG_DAC_CONTROL, &v);
	analog_enabled =
		(v & (ONYX_MUTE_RIGHT|ONYX_MUTE_LEFT))
		 != (ONYX_MUTE_RIGHT|ONYX_MUTE_LEFT);
	mutex_unlock(&onyx->mutex);

	switch (ti->tag) {
	case 0: return 1;
	case 1:	return analog_enabled;
	case 2: return spdif_enabled;
	}
	return 1;
}