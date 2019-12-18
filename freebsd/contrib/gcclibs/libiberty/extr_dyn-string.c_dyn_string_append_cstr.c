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
struct TYPE_4__ {scalar_t__ length; scalar_t__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dyn_string_resize (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char const*) ; 
 int strlen (char const*) ; 

int
dyn_string_append_cstr (dyn_string_t dest, const char *s)
{
  int len = strlen (s);

  /* The new length is the old length plus the size of our string, plus
     one for the null at the end.  */
  if (dyn_string_resize (dest, dest->length + len) == NULL)
    return 0;
  strcpy (dest->s + dest->length, s);
  dest->length += len;
  return 1;
}