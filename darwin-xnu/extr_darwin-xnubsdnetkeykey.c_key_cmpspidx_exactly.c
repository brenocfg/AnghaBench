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
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_3__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct secpolicyindex {scalar_t__ prefs; scalar_t__ prefd; scalar_t__ ul_proto; scalar_t__ internal_if; TYPE_2__ dst_range; TYPE_1__ src_range; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ key_sockaddrcmp (struct sockaddr*,struct sockaddr*,int) ; 

__attribute__((used)) static int
key_cmpspidx_exactly(
					 struct secpolicyindex *spidx0,
					 struct secpolicyindex *spidx1)
{
	/* sanity */
	if (spidx0 == NULL && spidx1 == NULL)
		return 1;
	
	if (spidx0 == NULL || spidx1 == NULL)
		return 0;
	
	if (spidx0->prefs != spidx1->prefs
		|| spidx0->prefd != spidx1->prefd
		|| spidx0->ul_proto != spidx1->ul_proto
		|| spidx0->internal_if != spidx1->internal_if)
		return 0;
	
	if (key_sockaddrcmp((struct sockaddr *)&spidx0->src,
						(struct sockaddr *)&spidx1->src, 1) != 0) {
		return 0;
	}
	if (key_sockaddrcmp((struct sockaddr *)&spidx0->dst,
						(struct sockaddr *)&spidx1->dst, 1) != 0) {
		return 0;
	}
    
    if (key_sockaddrcmp((struct sockaddr *)&spidx0->src_range.start,
						(struct sockaddr *)&spidx1->src_range.start, 1) != 0) {
		return 0;
	}
    if (key_sockaddrcmp((struct sockaddr *)&spidx0->src_range.end,
						(struct sockaddr *)&spidx1->src_range.end, 1) != 0) {
		return 0;
	}
	if (key_sockaddrcmp((struct sockaddr *)&spidx0->dst_range.start,
						(struct sockaddr *)&spidx1->dst_range.start, 1) != 0) {
		return 0;
	}
    if (key_sockaddrcmp((struct sockaddr *)&spidx0->dst_range.end,
						(struct sockaddr *)&spidx1->dst_range.end, 1) != 0) {
		return 0;
	}
	
	return 1;
}