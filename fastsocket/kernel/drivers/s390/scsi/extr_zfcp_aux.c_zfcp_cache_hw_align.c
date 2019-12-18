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
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 struct kmem_cache* kmem_cache_create (char const*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roundup_pow_of_two (unsigned long) ; 

__attribute__((used)) static struct kmem_cache *zfcp_cache_hw_align(const char *name,
					      unsigned long size)
{
	return kmem_cache_create(name, size, roundup_pow_of_two(size), 0, NULL);
}