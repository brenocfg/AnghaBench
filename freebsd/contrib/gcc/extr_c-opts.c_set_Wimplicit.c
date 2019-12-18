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

/* Variables and functions */
 int mesg_implicit_function_declaration ; 
 int warn_implicit ; 
 int warn_implicit_int ; 

__attribute__((used)) static void
set_Wimplicit (int on)
{
  warn_implicit = on;
  warn_implicit_int = on;
  if (on)
    {
      if (mesg_implicit_function_declaration != 2)
	mesg_implicit_function_declaration = 1;
    }
  else
    mesg_implicit_function_declaration = 0;
}