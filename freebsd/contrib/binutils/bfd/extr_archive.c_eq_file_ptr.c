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
struct ar_cache {scalar_t__ ptr; } ;
typedef  scalar_t__ PTR ;

/* Variables and functions */

__attribute__((used)) static int
eq_file_ptr (const PTR p1, const PTR p2)
{
  struct ar_cache *arc1 = (struct ar_cache *) p1;
  struct ar_cache *arc2 = (struct ar_cache *) p2;
  return arc1->ptr == arc2->ptr;
}