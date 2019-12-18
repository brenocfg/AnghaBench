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

/* Variables and functions */
 int /*<<< orphan*/  cfag12864b_mutex ; 
 int /*<<< orphan*/  cfag12864b_queue () ; 
 int cfag12864b_updating ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

unsigned char cfag12864b_enable(void)
{
	unsigned char ret;

	mutex_lock(&cfag12864b_mutex);

	if (!cfag12864b_updating) {
		cfag12864b_updating = 1;
		cfag12864b_queue();
		ret = 0;
	} else
		ret = 1;

	mutex_unlock(&cfag12864b_mutex);

	return ret;
}