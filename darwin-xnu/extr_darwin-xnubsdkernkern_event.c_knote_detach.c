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
struct knote {int dummy; } ;
struct klist {int dummy; } ;

/* Variables and functions */
 int SLIST_EMPTY (struct klist*) ; 
 int /*<<< orphan*/  SLIST_REMOVE (struct klist*,struct knote*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kn_selnext ; 
 int /*<<< orphan*/  knote ; 

int
knote_detach(struct klist *list, struct knote *kn)
{
	SLIST_REMOVE(list, kn, knote, kn_selnext);
	return (SLIST_EMPTY(list));
}