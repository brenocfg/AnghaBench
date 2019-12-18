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
struct TYPE_4__ {int length; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dyn_string_resize (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 

int
dyn_string_copy_cstr (dyn_string_t dest, const char *src)
{
  int length = strlen (src);
  /* Make room in DEST.  */
  if (dyn_string_resize (dest, length) == NULL)
    return 0;
  /* Copy DEST into SRC.  */
  strcpy (dest->s, src);
  /* Update the size of DEST.  */
  dest->length = length;
  return 1;
}