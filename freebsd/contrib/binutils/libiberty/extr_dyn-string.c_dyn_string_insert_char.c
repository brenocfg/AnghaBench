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
typedef  TYPE_1__* dyn_string_t ;
struct TYPE_4__ {int length; int* s; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dyn_string_resize (TYPE_1__*,int) ; 

int
dyn_string_insert_char (dyn_string_t dest, int pos, int c)
{
  int i;

  if (dyn_string_resize (dest, dest->length + 1) == NULL)
    return 0;
  /* Make room for the insertion.  Be sure to copy the NUL.  */
  for (i = dest->length; i >= pos; --i)
    dest->s[i + 1] = dest->s[i];
  /* Add the new character.  */
  dest->s[pos] = c;
  /* Compute the new length.  */
  ++dest->length;
  return 1;
}