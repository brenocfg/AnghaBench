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
struct TYPE_2__ {struct watch_adapter* node; } ;
struct watch_adapter {struct watch_adapter* token; TYPE_1__ watch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct watch_adapter*) ; 

__attribute__((used)) static void free_watch_adapter(struct watch_adapter *watch)
{
	kfree(watch->watch.node);
	kfree(watch->token);
	kfree(watch);
}