#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* gpio; } ;
struct tas {int hw_enabled; int /*<<< orphan*/  mtx; TYPE_1__ codec; } ;
struct codec_info_item {struct tas* codec_data; } ;
typedef  enum clock_switch { ____Placeholder_clock_switch } clock_switch ;
struct TYPE_7__ {TYPE_2__* methods; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* all_amps_restore ) (TYPE_3__*) ;int /*<<< orphan*/  (* all_amps_off ) (TYPE_3__*) ;} ;

/* Variables and functions */
#define  CLOCK_SWITCH_PREPARE_SLAVE 129 
#define  CLOCK_SWITCH_SLAVE 128 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  tas_reset_init (struct tas*) ; 
 int /*<<< orphan*/  tas_set_mixer (struct tas*) ; 
 int /*<<< orphan*/  tas_set_volume (struct tas*) ; 

__attribute__((used)) static int tas_switch_clock(struct codec_info_item *cii, enum clock_switch clock)
{
	struct tas *tas = cii->codec_data;

	switch(clock) {
	case CLOCK_SWITCH_PREPARE_SLAVE:
		/* Clocks are going away, mute mute mute */
		tas->codec.gpio->methods->all_amps_off(tas->codec.gpio);
		tas->hw_enabled = 0;
		break;
	case CLOCK_SWITCH_SLAVE:
		/* Clocks are back, re-init the codec */
		mutex_lock(&tas->mtx);
		tas_reset_init(tas);
		tas_set_volume(tas);
		tas_set_mixer(tas);
		tas->hw_enabled = 1;
		tas->codec.gpio->methods->all_amps_restore(tas->codec.gpio);
		mutex_unlock(&tas->mtx);
		break;
	default:
		/* doesn't happen as of now */
		return -EINVAL;
	}
	return 0;
}