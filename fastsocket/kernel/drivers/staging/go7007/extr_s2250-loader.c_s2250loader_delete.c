#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kref {int dummy; } ;
typedef  TYPE_1__* pdevice_extension_t ;
struct TYPE_4__ {size_t minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/ ** s2250_dev_table ; 
 TYPE_1__* to_s2250loader_dev_common (struct kref*) ; 

__attribute__((used)) static void s2250loader_delete(struct kref *kref)
{
	pdevice_extension_t s = to_s2250loader_dev_common(kref);
	s2250_dev_table[s->minor] = NULL;
	kfree(s);
}