#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct inf {TYPE_1__* task; } ;
typedef  int /*<<< orphan*/  mach_port_type_t ;
typedef  scalar_t__ error_t ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORTINFO_DETAILS ; 
 struct inf* active_inf () ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct value* parse_to_comma_and_eval (char**) ; 
 scalar_t__ print_port_info (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ print_task_ports_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  stdout ; 
 long value_as_long (struct value*) ; 
 int /*<<< orphan*/  value_free_to_mark (struct value*) ; 
 struct value* value_mark () ; 

__attribute__((used)) static void
info_port_rights (char *args, mach_port_type_t only)
{
  struct inf *inf = active_inf ();
  struct value *vmark = value_mark ();

  if (args)
    /* Explicit list of port rights.  */
    {
      while (*args)
	{
	  struct value *val = parse_to_comma_and_eval (&args);
	  long right = value_as_long (val);
	  error_t err =
	  print_port_info (right, 0, inf->task->port, PORTINFO_DETAILS,
			   stdout);
	  if (err)
	    error ("%ld: %s.", right, safe_strerror (err));
	}
    }
  else
    /* Print all of them.  */
    {
      error_t err =
      print_task_ports_info (inf->task->port, only, PORTINFO_DETAILS,
			     stdout);
      if (err)
	error ("%s.", safe_strerror (err));
    }

  value_free_to_mark (vmark);
}