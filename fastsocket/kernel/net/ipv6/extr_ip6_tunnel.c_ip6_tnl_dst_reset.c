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
struct ip6_tnl {int /*<<< orphan*/ * dst_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ip6_tnl_dst_reset(struct ip6_tnl *t)
{
	dst_release(t->dst_cache);
	t->dst_cache = NULL;
}