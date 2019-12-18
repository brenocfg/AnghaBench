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
struct TYPE_2__ {struct ocontext* name; } ;
struct ocontext {TYPE_1__ u; int /*<<< orphan*/ * context; } ;

/* Variables and functions */
 int OCON_FS ; 
 int OCON_FSUSE ; 
 int OCON_ISID ; 
 int OCON_NETIF ; 
 int /*<<< orphan*/  context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ocontext*) ; 

__attribute__((used)) static void ocontext_destroy(struct ocontext *c, int i)
{
	if (!c)
		return;

	context_destroy(&c->context[0]);
	context_destroy(&c->context[1]);
	if (i == OCON_ISID || i == OCON_FS ||
	    i == OCON_NETIF || i == OCON_FSUSE)
		kfree(c->u.name);
	kfree(c);
}