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
struct protosw {int dummy; } ;
struct domain {int dom_flags; } ;

/* Variables and functions */
 int DOM_INITIALIZED ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int key_proto_count ; 
 struct domain* keydomain ; 
 struct protosw* keysw ; 
 int /*<<< orphan*/  net_add_proto (struct protosw*,struct domain*,int) ; 

__attribute__((used)) static void
key_dinit(struct domain *dp)
{
	struct protosw *pr;
	int i;

	VERIFY(!(dp->dom_flags & DOM_INITIALIZED));
	VERIFY(keydomain == NULL);

	keydomain = dp;

	for (i = 0, pr = &keysw[0]; i < key_proto_count; i++, pr++)
		net_add_proto(pr, dp, 1);
}