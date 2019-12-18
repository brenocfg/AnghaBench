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
struct dummy_frame {int /*<<< orphan*/  regcache; struct dummy_frame* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  regcache_xfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct dummy_frame*) ; 

__attribute__((used)) static void
discard_innermost_dummy (struct dummy_frame **stack)
{
  struct dummy_frame *tbd = (*stack);
  (*stack) = (*stack)->next;
  regcache_xfree (tbd->regcache);
  xfree (tbd);
}