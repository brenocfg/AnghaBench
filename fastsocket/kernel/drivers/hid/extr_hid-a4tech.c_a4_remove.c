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
struct hid_device {int dummy; } ;
struct a4tech_sc {int dummy; } ;

/* Variables and functions */
 struct a4tech_sc* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (struct a4tech_sc*) ; 

__attribute__((used)) static void a4_remove(struct hid_device *hdev)
{
	struct a4tech_sc *a4 = hid_get_drvdata(hdev);

	hid_hw_stop(hdev);
	kfree(a4);
}