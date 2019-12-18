#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct foo_obj {int baz; int bar; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct foo_attribute {TYPE_1__ attr; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t b_store(struct foo_obj *foo_obj, struct foo_attribute *attr,
		       const char *buf, size_t count)
{
	int var;

	sscanf(buf, "%du", &var);
	if (strcmp(attr->attr.name, "baz") == 0)
		foo_obj->baz = var;
	else
		foo_obj->bar = var;
	return count;
}