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
struct TYPE_5__ {scalar_t__ length; scalar_t__ s; } ;

/* Variables and functions */
 scalar_t__ dyn_string_resize (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,scalar_t__) ; 

int
dyn_string_append (dyn_string_t dest, dyn_string_t s)
{
  if (dyn_string_resize (dest, dest->length + s->length) == 0)
    return 0;
  strcpy (dest->s + dest->length, s->s);
  dest->length += s->length;
  return 1;
}