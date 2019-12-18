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
typedef  int /*<<< orphan*/  u16 ;
struct si4713_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mute; scalar_t__ power_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI4713_TX_LINE_INPUT_MUTE ; 
 int /*<<< orphan*/  get_mute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_mute (int /*<<< orphan*/ ) ; 
 int si4713_write_property (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si4713_set_mute(struct si4713_device *sdev, u16 mute)
{
	int rval = 0;

	mute = set_mute(mute);

	mutex_lock(&sdev->mutex);

	if (sdev->power_state)
		rval = si4713_write_property(sdev,
				SI4713_TX_LINE_INPUT_MUTE, mute);

	if (rval >= 0)
		sdev->mute = get_mute(mute);

	mutex_unlock(&sdev->mutex);

	return rval;
}