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
struct macro_buffer {int size; int /*<<< orphan*/  text; int /*<<< orphan*/  shared; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  xrealloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
resize_buffer (struct macro_buffer *b, int n)
{
  /* We shouldn't be trying to resize shared strings.  */
  gdb_assert (! b->shared);
  
  if (b->size == 0)
    b->size = n;
  else
    while (b->size <= n)
      b->size *= 2;

  b->text = xrealloc (b->text, b->size);
}