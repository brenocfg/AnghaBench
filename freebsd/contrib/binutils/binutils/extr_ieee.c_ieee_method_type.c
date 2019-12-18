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
struct ieee_handle {int dummy; } ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ ieee_function_type (void*,int,scalar_t__) ; 
 int /*<<< orphan*/  ieee_pop_unused_type (struct ieee_handle*) ; 

__attribute__((used)) static bfd_boolean
ieee_method_type (void *p, bfd_boolean domain, int argcount,
		  bfd_boolean varargs)
{
  struct ieee_handle *info = (struct ieee_handle *) p;

  /* FIXME: The MRI/HP IEEE spec defines a pmisc record to use for a
     method, but the definition is incomplete.  We just output an 'x'
     type.  */

  if (domain)
    ieee_pop_unused_type (info);

  return ieee_function_type (p, argcount, varargs);
}