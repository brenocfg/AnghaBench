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
struct macro_buffer {int /*<<< orphan*/  text; scalar_t__ size; int /*<<< orphan*/  shared; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_buffer (struct macro_buffer *b)
{
  gdb_assert (! b->shared);
  if (b->size)
    xfree (b->text);
}