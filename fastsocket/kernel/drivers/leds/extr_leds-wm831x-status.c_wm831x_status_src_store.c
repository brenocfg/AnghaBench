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
struct wm831x_status {int src; int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct led_classdev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * led_src_texts ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 struct wm831x_status* to_wm831x_status (struct led_classdev*) ; 

__attribute__((used)) static ssize_t wm831x_status_src_store(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t size)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct wm831x_status *led = to_wm831x_status(led_cdev);
	char name[20];
	int i;
	size_t len;

	name[sizeof(name) - 1] = '\0';
	strncpy(name, buf, sizeof(name) - 1);
	len = strlen(name);

	if (len && name[len - 1] == '\n')
		name[len - 1] = '\0';

	for (i = 0; i < ARRAY_SIZE(led_src_texts); i++) {
		if (!strcmp(name, led_src_texts[i])) {
			mutex_lock(&led->mutex);

			led->src = i;
			schedule_work(&led->work);

			mutex_unlock(&led->mutex);
		}
	}

	return size;
}