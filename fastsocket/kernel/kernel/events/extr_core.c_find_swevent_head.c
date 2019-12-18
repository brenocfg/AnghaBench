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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct swevent_htable {int /*<<< orphan*/  swevent_hlist; } ;
struct swevent_hlist {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  config; } ;
struct perf_event {TYPE_1__ attr; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 struct hlist_head* __find_swevent_head (struct swevent_hlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct swevent_hlist* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hlist_head *
find_swevent_head(struct swevent_htable *swhash, struct perf_event *event)
{
	struct swevent_hlist *hlist;
	u32 event_id = event->attr.config;
	u64 type = event->attr.type;

	/*
	 * Event scheduling is always serialized against hlist allocation
	 * and release. Which makes the protected version suitable here.
	 * The context lock guarantees that.
	 */
	hlist = rcu_dereference(swhash->swevent_hlist);
	if (!hlist)
		return NULL;

	return __find_swevent_head(hlist, type, event_id);
}