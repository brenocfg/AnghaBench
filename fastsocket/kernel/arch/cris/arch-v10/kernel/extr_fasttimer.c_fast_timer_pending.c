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
struct fast_timer {int /*<<< orphan*/ * prev; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 struct fast_timer const* fast_timer_list ; 

__attribute__((used)) static inline int fast_timer_pending (const struct fast_timer * t)
{
  return (t->next != NULL) || (t->prev != NULL) || (t == fast_timer_list);
}