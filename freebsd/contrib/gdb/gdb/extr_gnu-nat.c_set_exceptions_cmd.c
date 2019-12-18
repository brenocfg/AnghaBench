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
struct inf {int want_exceptions; scalar_t__ task; } ;

/* Variables and functions */
 struct inf* cur_inf () ; 
 int parse_bool_arg (char*,char*) ; 

__attribute__((used)) static void
set_exceptions_cmd (char *args, int from_tty)
{
  struct inf *inf = cur_inf ();
  int val = parse_bool_arg (args, "set exceptions");

  if (inf->task && inf->want_exceptions != val)
    /* Make this take effect immediately in a running process.  */
    /* XXX */ ;

  inf->want_exceptions = val;
}