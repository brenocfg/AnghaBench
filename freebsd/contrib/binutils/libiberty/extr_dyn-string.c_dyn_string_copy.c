#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dyn_string_t ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * dyn_string_resize (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dyn_string_copy (dyn_string_t dest, dyn_string_t src)
{
  if (dest == src)
    abort ();

  /* Make room in DEST.  */
  if (dyn_string_resize (dest, src->length) == NULL)
    return 0;
  /* Copy DEST into SRC.  */
  strcpy (dest->s, src->s);
  /* Update the size of DEST.  */
  dest->length = src->length;
  return 1;
}