#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bitmap ;
struct TYPE_4__ {scalar_t__ first; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_elt_clear_from (TYPE_1__*,scalar_t__) ; 

inline void
bitmap_clear (bitmap head)
{
  if (head->first)
    bitmap_elt_clear_from (head, head->first);
}