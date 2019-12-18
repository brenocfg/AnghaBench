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
struct pernet_operations {int (* init ) (int /*<<< orphan*/ *) ;} ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_net ; 
 int stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int register_pernet_operations(struct list_head *list,
				      struct pernet_operations *ops)
{
	if (ops->init == NULL)
		return 0;
	return ops->init(&init_net);
}