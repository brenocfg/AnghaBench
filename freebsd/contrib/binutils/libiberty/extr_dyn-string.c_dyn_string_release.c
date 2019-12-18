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
struct TYPE_4__ {char* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

char*
dyn_string_release (dyn_string_t ds)
{
  /* Store the old buffer.  */
  char* result = ds->s;
  /* The buffer is no longer owned by DS.  */
  ds->s = NULL;
  /* Delete DS.  */
  free (ds);
  /* Return the old buffer.  */
  return result;
}