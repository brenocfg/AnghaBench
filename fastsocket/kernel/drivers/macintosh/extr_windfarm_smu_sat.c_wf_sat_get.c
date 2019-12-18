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
struct wf_sensor {int dummy; } ;
struct wf_sat_sensor {int index; int shift; int index2; struct wf_sat* sat; } ;
struct wf_sat {int* cache; int /*<<< orphan*/  mutex; scalar_t__ last_read; int /*<<< orphan*/ * i2c; } ;
typedef  int s32 ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MAX_AGE ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int wf_sat_read_cache (struct wf_sat*) ; 
 struct wf_sat_sensor* wf_to_sat (struct wf_sensor*) ; 

__attribute__((used)) static int wf_sat_get(struct wf_sensor *sr, s32 *value)
{
	struct wf_sat_sensor *sens = wf_to_sat(sr);
	struct wf_sat *sat = sens->sat;
	int i, err;
	s32 val;

	if (sat->i2c == NULL)
		return -ENODEV;

	mutex_lock(&sat->mutex);
	if (time_after(jiffies, (sat->last_read + MAX_AGE))) {
		err = wf_sat_read_cache(sat);
		if (err)
			goto fail;
	}

	i = sens->index * 2;
	val = ((sat->cache[i] << 8) + sat->cache[i+1]) << sens->shift;
	if (sens->index2 >= 0) {
		i = sens->index2 * 2;
		/* 4.12 * 8.8 -> 12.20; shift right 4 to get 16.16 */
		val = (val * ((sat->cache[i] << 8) + sat->cache[i+1])) >> 4;
	}

	*value = val;
	err = 0;

 fail:
	mutex_unlock(&sat->mutex);
	return err;
}