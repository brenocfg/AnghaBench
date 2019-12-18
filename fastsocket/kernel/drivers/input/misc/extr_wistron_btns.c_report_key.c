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

/* Variables and functions */
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void report_key(struct input_dev *dev, unsigned int keycode)
{
	input_report_key(dev, keycode, 1);
	input_sync(dev);
	input_report_key(dev, keycode, 0);
	input_sync(dev);
}