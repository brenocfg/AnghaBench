#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bitmap_set_t ;
struct TYPE_3__ {void* values; void* expressions; } ;

/* Variables and functions */
 void* BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_set_pool ; 
 int /*<<< orphan*/  grand_bitmap_obstack ; 
 int /*<<< orphan*/  pool_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bitmap_set_t
bitmap_set_new (void)
{
  bitmap_set_t ret = (bitmap_set_t) pool_alloc (bitmap_set_pool);
  ret->expressions = BITMAP_ALLOC (&grand_bitmap_obstack);
  ret->values = BITMAP_ALLOC (&grand_bitmap_obstack);
  return ret;
}