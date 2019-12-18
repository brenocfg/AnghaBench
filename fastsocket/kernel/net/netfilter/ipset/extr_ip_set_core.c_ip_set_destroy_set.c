#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ip_set {TYPE_2__* type; TYPE_1__* variant; int /*<<< orphan*/  name; } ;
typedef  size_t ip_set_id_t ;
struct TYPE_4__ {int /*<<< orphan*/  me; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy ) (struct ip_set*) ;} ;

/* Variables and functions */
 struct ip_set** ip_set_list ; 
 int /*<<< orphan*/  kfree (struct ip_set*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ip_set*) ; 

__attribute__((used)) static void
ip_set_destroy_set(ip_set_id_t index)
{
	struct ip_set *set = ip_set_list[index];

	pr_debug("set: %s\n",  set->name);
	ip_set_list[index] = NULL;

	/* Must call it without holding any lock */
	set->variant->destroy(set);
	module_put(set->type->me);
	kfree(set);
}