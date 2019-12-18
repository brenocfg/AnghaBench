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
struct swevent_htable {int /*<<< orphan*/  swevent_hlist; } ;
struct swevent_hlist {int dummy; } ;

/* Variables and functions */
 struct swevent_hlist* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct swevent_hlist *
swevent_hlist_deref(struct swevent_htable *swhash)
{
	return rcu_dereference(swhash->swevent_hlist);
}