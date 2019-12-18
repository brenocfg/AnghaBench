#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct bd2802_led {int adf_on; TYPE_2__* client; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_1__ attr; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__**) ; 
 TYPE_3__** bd2802_addr_attributes ; 
 scalar_t__ bd2802_is_all_off (struct bd2802_led*) ; 
 int /*<<< orphan*/  bd2802_reset_cancel (struct bd2802_led*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int device_create_file (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void bd2802_enable_adv_conf(struct bd2802_led *led)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(bd2802_addr_attributes); i++) {
		ret = device_create_file(&led->client->dev,
						bd2802_addr_attributes[i]);
		if (ret) {
			dev_err(&led->client->dev, "failed: sysfs file %s\n",
					bd2802_addr_attributes[i]->attr.name);
			goto failed_remove_files;
		}
	}

	if (bd2802_is_all_off(led))
		bd2802_reset_cancel(led);

	led->adf_on = 1;

	return;

failed_remove_files:
	for (i--; i >= 0; i--)
		device_remove_file(&led->client->dev,
						bd2802_addr_attributes[i]);
}