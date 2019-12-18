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
struct value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  value_logical_not (struct value*) ; 

int
value_true (struct value *val)
{
  /* It is possible that we should have some sort of error if a non-boolean
     value is used in this context.  Possibly dependent on some kind of
     "boolean-checking" option like range checking.  But it should probably
     not depend on the language except insofar as is necessary to identify
     a "boolean" value (i.e. in C using a float, pointer, etc., as a boolean
     should be an error, probably).  */
  return !value_logical_not (val);
}