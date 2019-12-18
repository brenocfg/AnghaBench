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
struct pr_handle {int dummy; } ;
typedef  int bfd_boolean ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ append_type (struct pr_handle*,char*) ; 
 char* pop_type (struct pr_handle*) ; 
 scalar_t__ prepend_type (struct pr_handle*,char*) ; 
 scalar_t__ substitute_type (struct pr_handle*,char*) ; 

__attribute__((used)) static bfd_boolean
pr_offset_type (void *p)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *t;

  if (! substitute_type (info, ""))
    return FALSE;

  t = pop_type (info);
  if (t == NULL)
    return FALSE;

  return (substitute_type (info, "")
	  && prepend_type (info, " ")
	  && prepend_type (info, t)
	  && append_type (info, "::|"));
}