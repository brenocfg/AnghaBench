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
typedef  int /*<<< orphan*/  bitmap_obstack ;
typedef  TYPE_1__* bitmap ;
struct TYPE_3__ {int /*<<< orphan*/ * obstack; int /*<<< orphan*/ * current; int /*<<< orphan*/  first; } ;

/* Variables and functions */

__attribute__((used)) static inline void
bitmap_initialize (bitmap head, bitmap_obstack *obstack)
{
  head->first = head->current = NULL;
  head->obstack = obstack;
}