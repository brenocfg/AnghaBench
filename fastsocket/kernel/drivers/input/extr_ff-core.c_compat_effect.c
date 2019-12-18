#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fade_level; int /*<<< orphan*/  fade_length; int /*<<< orphan*/  attack_level; int /*<<< orphan*/  attack_length; } ;
struct TYPE_7__ {int period; TYPE_2__ envelope; int /*<<< orphan*/  phase; int /*<<< orphan*/  offset; int /*<<< orphan*/  magnitude; int /*<<< orphan*/  waveform; } ;
struct TYPE_5__ {int strong_magnitude; int weak_magnitude; } ;
struct TYPE_8__ {TYPE_3__ periodic; TYPE_1__ rumble; } ;
struct ff_effect {int type; TYPE_4__ u; } ;
struct ff_device {int /*<<< orphan*/  ffbit; } ;

/* Variables and functions */
 int EINVAL ; 
 int FF_PERIODIC ; 
#define  FF_RUMBLE 128 
 int /*<<< orphan*/  FF_SINE ; 
 int /*<<< orphan*/  max (int,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compat_effect(struct ff_device *ff, struct ff_effect *effect)
{
	int magnitude;

	switch (effect->type) {
	case FF_RUMBLE:
		if (!test_bit(FF_PERIODIC, ff->ffbit))
			return -EINVAL;

		/*
		 * calculate manginude of sine wave as average of rumble's
		 * 2/3 of strong magnitude and 1/3 of weak magnitude
		 */
		magnitude = effect->u.rumble.strong_magnitude / 3 +
			    effect->u.rumble.weak_magnitude / 6;

		effect->type = FF_PERIODIC;
		effect->u.periodic.waveform = FF_SINE;
		effect->u.periodic.period = 50;
		effect->u.periodic.magnitude = max(magnitude, 0x7fff);
		effect->u.periodic.offset = 0;
		effect->u.periodic.phase = 0;
		effect->u.periodic.envelope.attack_length = 0;
		effect->u.periodic.envelope.attack_level = 0;
		effect->u.periodic.envelope.fade_length = 0;
		effect->u.periodic.envelope.fade_level = 0;

		return 0;

	default:
		/* Let driver handle conversion */
		return 0;
	}
}