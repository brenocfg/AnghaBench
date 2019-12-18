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
struct input_dev {int dummy; } ;
struct hidp_session {int dummy; } ;
struct hid_device {struct hidp_session* driver_data; } ;

/* Variables and functions */
 int hidp_queue_event (struct hidp_session*,struct input_dev*,unsigned int,unsigned int,int) ; 
 struct hid_device* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int hidp_hidinput_event(struct input_dev *dev, unsigned int type, unsigned int code, int value)
{
	struct hid_device *hid = input_get_drvdata(dev);
	struct hidp_session *session = hid->driver_data;

	return hidp_queue_event(session, dev, type, code, value);
}