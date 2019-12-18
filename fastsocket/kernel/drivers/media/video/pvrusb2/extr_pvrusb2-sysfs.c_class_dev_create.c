#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int /*<<< orphan*/  dev; } ;
struct pvr2_sysfs_class {int /*<<< orphan*/  class; } ;
struct TYPE_5__ {char* name; void* mode; } ;
struct TYPE_6__ {int /*<<< orphan*/ * store; int /*<<< orphan*/  show; TYPE_2__ attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  hdw; } ;
struct pvr2_sysfs {int v4l_minor_number_created_ok; int v4l_radio_minor_number_created_ok; int unit_number_created_ok; int bus_info_created_ok; int hdw_name_created_ok; int hdw_desc_created_ok; TYPE_3__ attr_hdw_desc; struct device* class_dev; TYPE_3__ attr_hdw_name; TYPE_3__ attr_bus_info; TYPE_3__ attr_unit_number; TYPE_3__ attr_v4l_radio_minor_number; TYPE_3__ attr_v4l_minor_number; TYPE_1__ channel; } ;
struct device {int /*<<< orphan*/  parent; int /*<<< orphan*/ * class; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 void* S_IRUGO ; 
 int /*<<< orphan*/  bus_info_show ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct pvr2_sysfs*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_create_file (struct device*,TYPE_3__*) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdw_desc_show ; 
 int /*<<< orphan*/  hdw_name_show ; 
 struct device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct usb_device* pvr2_hdw_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_hdw_get_device_identifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_sysfs_add_controls (struct pvr2_sysfs*) ; 
 int /*<<< orphan*/  pvr2_sysfs_add_debugifc (struct pvr2_sysfs*) ; 
 int /*<<< orphan*/  pvr2_sysfs_trace (char*,struct device*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  unit_number_show ; 
 int /*<<< orphan*/  v4l_minor_number_show ; 
 int /*<<< orphan*/  v4l_radio_minor_number_show ; 

__attribute__((used)) static void class_dev_create(struct pvr2_sysfs *sfp,
			     struct pvr2_sysfs_class *class_ptr)
{
	struct usb_device *usb_dev;
	struct device *class_dev;
	int ret;

	usb_dev = pvr2_hdw_get_dev(sfp->channel.hdw);
	if (!usb_dev) return;
	class_dev = kzalloc(sizeof(*class_dev),GFP_KERNEL);
	if (!class_dev) return;

	pvr2_sysfs_trace("Creating class_dev id=%p",class_dev);

	class_dev->class = &class_ptr->class;

	dev_set_name(class_dev, "%s",
		     pvr2_hdw_get_device_identifier(sfp->channel.hdw));

	class_dev->parent = get_device(&usb_dev->dev);

	sfp->class_dev = class_dev;
	dev_set_drvdata(class_dev, sfp);
	ret = device_register(class_dev);
	if (ret) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_register failed");
		put_device(class_dev);
		return;
	}
	sfp->attr_v4l_minor_number.attr.name = "v4l_minor_number";
	sfp->attr_v4l_minor_number.attr.mode = S_IRUGO;
	sfp->attr_v4l_minor_number.show = v4l_minor_number_show;
	sfp->attr_v4l_minor_number.store = NULL;
	ret = device_create_file(sfp->class_dev,
				       &sfp->attr_v4l_minor_number);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	} else {
		sfp->v4l_minor_number_created_ok = !0;
	}
	sfp->attr_v4l_radio_minor_number.attr.name = "v4l_radio_minor_number";
	sfp->attr_v4l_radio_minor_number.attr.mode = S_IRUGO;
	sfp->attr_v4l_radio_minor_number.show = v4l_radio_minor_number_show;
	sfp->attr_v4l_radio_minor_number.store = NULL;
	ret = device_create_file(sfp->class_dev,
				       &sfp->attr_v4l_radio_minor_number);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	} else {
		sfp->v4l_radio_minor_number_created_ok = !0;
	}
	sfp->attr_unit_number.attr.name = "unit_number";
	sfp->attr_unit_number.attr.mode = S_IRUGO;
	sfp->attr_unit_number.show = unit_number_show;
	sfp->attr_unit_number.store = NULL;
	ret = device_create_file(sfp->class_dev,&sfp->attr_unit_number);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	} else {
		sfp->unit_number_created_ok = !0;
	}
	sfp->attr_bus_info.attr.name = "bus_info_str";
	sfp->attr_bus_info.attr.mode = S_IRUGO;
	sfp->attr_bus_info.show = bus_info_show;
	sfp->attr_bus_info.store = NULL;
	ret = device_create_file(sfp->class_dev,
				       &sfp->attr_bus_info);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	} else {
		sfp->bus_info_created_ok = !0;
	}
	sfp->attr_hdw_name.attr.name = "device_hardware_type";
	sfp->attr_hdw_name.attr.mode = S_IRUGO;
	sfp->attr_hdw_name.show = hdw_name_show;
	sfp->attr_hdw_name.store = NULL;
	ret = device_create_file(sfp->class_dev,
				 &sfp->attr_hdw_name);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	} else {
		sfp->hdw_name_created_ok = !0;
	}
	sfp->attr_hdw_desc.attr.name = "device_hardware_description";
	sfp->attr_hdw_desc.attr.mode = S_IRUGO;
	sfp->attr_hdw_desc.show = hdw_desc_show;
	sfp->attr_hdw_desc.store = NULL;
	ret = device_create_file(sfp->class_dev,
				 &sfp->attr_hdw_desc);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "device_create_file error: %d",
			   ret);
	} else {
		sfp->hdw_desc_created_ok = !0;
	}

	pvr2_sysfs_add_controls(sfp);
#ifdef CONFIG_VIDEO_PVRUSB2_DEBUGIFC
	pvr2_sysfs_add_debugifc(sfp);
#endif /* CONFIG_VIDEO_PVRUSB2_DEBUGIFC */
}