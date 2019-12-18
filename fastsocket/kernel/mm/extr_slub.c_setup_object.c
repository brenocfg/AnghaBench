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
struct page {int dummy; } ;
struct kmem_cache {int /*<<< orphan*/  (* ctor ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  setup_object_debug (struct kmem_cache*,struct page*,void*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/  (*) (void*)) ; 

__attribute__((used)) static void setup_object(struct kmem_cache *s, struct page *page,
				void *object)
{
	setup_object_debug(s, page, object);
	if (unlikely(s->ctor))
		s->ctor(object);
}