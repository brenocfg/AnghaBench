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
struct usb_ov511 {int /*<<< orphan*/  sensor; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct usb_ov511* cd_to_ov (struct device*) ; 
 int /*<<< orphan*/  senlist ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 char* symbolic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_sensor(struct device *cd,
			   struct device_attribute *attr, char *buf)
{
	struct usb_ov511 *ov = cd_to_ov(cd);
	return sprintf(buf, "%s\n", symbolic(senlist, ov->sensor));
}