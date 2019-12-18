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
struct mfc6_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct mfc6_cache*) ; 
 int /*<<< orphan*/  mfc6_net (struct mfc6_cache*) ; 
 int /*<<< orphan*/  mrt_cachep ; 
 int /*<<< orphan*/  release_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ip6mr_cache_free(struct mfc6_cache *c)
{
	release_net(mfc6_net(c));
	kmem_cache_free(mrt_cachep, c);
}