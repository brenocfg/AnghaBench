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
struct TYPE_3__ {int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ebitmap_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mls_context_init (struct context*) ; 
 int /*<<< orphan*/  selinux_mls_enabled ; 

__attribute__((used)) static inline void mls_context_destroy(struct context *c)
{
	if (!selinux_mls_enabled)
		return;

	ebitmap_destroy(&c->range.level[0].cat);
	ebitmap_destroy(&c->range.level[1].cat);
	mls_context_init(c);
}