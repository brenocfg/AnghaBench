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
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dyn_string_eq (dyn_string_t ds1, dyn_string_t ds2)
{
  /* If DS1 and DS2 have different lengths, they must not be the same.  */
  if (ds1->length != ds2->length)
    return 0;
  else
    return !strcmp (ds1->s, ds2->s);
}