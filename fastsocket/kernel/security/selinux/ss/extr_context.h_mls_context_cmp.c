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
struct TYPE_4__ {TYPE_1__* level; } ;
struct context {TYPE_2__ range; } ;
struct TYPE_3__ {scalar_t__ sens; int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 scalar_t__ ebitmap_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_mls_enabled ; 

__attribute__((used)) static inline int mls_context_cmp(struct context *c1, struct context *c2)
{
	if (!selinux_mls_enabled)
		return 1;

	return ((c1->range.level[0].sens == c2->range.level[0].sens) &&
		ebitmap_cmp(&c1->range.level[0].cat, &c2->range.level[0].cat) &&
		(c1->range.level[1].sens == c2->range.level[1].sens) &&
		ebitmap_cmp(&c1->range.level[1].cat, &c2->range.level[1].cat));
}