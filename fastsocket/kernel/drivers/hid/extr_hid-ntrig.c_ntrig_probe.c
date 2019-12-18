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
struct ntrig_data {scalar_t__ found_contact_id; scalar_t__ reading_a_point; } ;
struct hid_device_id {int dummy; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct ntrig_data*) ; 
 int /*<<< orphan*/  kfree (struct ntrig_data*) ; 
 struct ntrig_data* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ntrig_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;
	struct ntrig_data *nd;

	nd = kmalloc(sizeof(struct ntrig_data), GFP_KERNEL);
	if (!nd) {
		dev_err(&hdev->dev, "cannot allocate N-Trig data\n");
		return -ENOMEM;
	}
	nd->reading_a_point = 0;
	nd->found_contact_id = 0;
	hid_set_drvdata(hdev, nd);

	ret = hid_parse(hdev);
	if (!ret)
		ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);

	if (ret)
		kfree (nd);

	return ret;
}