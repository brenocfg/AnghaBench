#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* key_name; struct TYPE_3__* dn; } ;
typedef  TYPE_1__ test_trust_anchor ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

__attribute__((used)) static void
free_trust_anchor(void *value)
{
	test_trust_anchor *ttc;

	ttc = value;
	xfree(ttc->dn);
	xfree(ttc->key_name);
	xfree(ttc);
}