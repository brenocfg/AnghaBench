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
struct inf {scalar_t__ want_signals; scalar_t__ traced; scalar_t__ task; } ;

/* Variables and functions */
 struct inf* cur_inf () ; 
 int /*<<< orphan*/  inf_set_traced (struct inf*,scalar_t__) ; 
 scalar_t__ parse_bool_arg (char*,char*) ; 

__attribute__((used)) static void
set_signals_cmd (char *args, int from_tty)
{
  struct inf *inf = cur_inf ();

  inf->want_signals = parse_bool_arg (args, "set signals");

  if (inf->task && inf->want_signals != inf->traced)
    /* Make this take effect immediately in a running process.  */
    inf_set_traced (inf, inf->want_signals);
}