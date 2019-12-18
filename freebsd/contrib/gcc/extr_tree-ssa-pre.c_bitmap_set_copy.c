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
typedef  TYPE_1__* bitmap_set_t ;
struct TYPE_4__ {int /*<<< orphan*/  values; int /*<<< orphan*/  expressions; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bitmap_set_copy (bitmap_set_t dest, bitmap_set_t orig)
{
  bitmap_copy (dest->expressions, orig->expressions);
  bitmap_copy (dest->values, orig->values);
}