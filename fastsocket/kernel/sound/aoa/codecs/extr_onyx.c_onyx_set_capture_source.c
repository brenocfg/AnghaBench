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
struct onyx {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ONYX_ADC_INPUT_MIC ; 
 int /*<<< orphan*/  ONYX_REG_ADC_CONTROL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onyx_read_register (struct onyx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onyx_write_register (struct onyx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void onyx_set_capture_source(struct onyx *onyx, int mic)
{
	s8 v;

	mutex_lock(&onyx->mutex);
	onyx_read_register(onyx, ONYX_REG_ADC_CONTROL, &v);
	v &= ~ONYX_ADC_INPUT_MIC;
	if (mic)
		v |= ONYX_ADC_INPUT_MIC;
	onyx_write_register(onyx, ONYX_REG_ADC_CONTROL, v);
	mutex_unlock(&onyx->mutex);
}