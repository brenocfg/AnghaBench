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
dyn_string_append_char (dyn_string_t dest, int c)
{
  /* Make room for the extra character.  */
  if (dyn_string_resize (dest, dest->length + 1) == NULL)
    return 0;
  /* Append the character; it will overwrite the old NUL.  */
  dest->s[dest->length] = c;
  /* Add a new NUL at the end.  */
  dest->s[dest->length + 1] = '\0';
  /* Update the length.  */
  ++(dest->length);
  return 1;
}