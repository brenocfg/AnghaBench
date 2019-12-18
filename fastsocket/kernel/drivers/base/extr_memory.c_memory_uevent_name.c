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
struct kset {int dummy; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 char const* MEMORY_CLASS_NAME ; 

__attribute__((used)) static const char *memory_uevent_name(struct kset *kset, struct kobject *kobj)
{
	return MEMORY_CLASS_NAME;
}