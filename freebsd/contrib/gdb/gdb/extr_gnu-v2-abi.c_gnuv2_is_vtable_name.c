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
 scalar_t__ is_cplus_marker (char const) ; 

__attribute__((used)) static int
gnuv2_is_vtable_name (const char *name)
{
  return (((name)[0] == '_'
	   && (((name)[1] == 'V' && (name)[2] == 'T')
	       || ((name)[1] == 'v' && (name)[2] == 't'))
	   && is_cplus_marker ((name)[3])) ||
	  ((name)[0] == '_' && (name)[1] == '_'
	   && (name)[2] == 'v' && (name)[3] == 't' && (name)[4] == '_'));
}