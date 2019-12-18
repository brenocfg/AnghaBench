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
struct macro_buffer {int size; char* text; int last_token; scalar_t__ shared; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
init_buffer (struct macro_buffer *b, int n)
{
  /* Small value for initial testing.  */
  n = 1;

  b->size = n;
  if (n > 0)
    b->text = (char *) xmalloc (n);
  else
    b->text = NULL;
  b->len = 0;
  b->shared = 0;
  b->last_token = -1;
}