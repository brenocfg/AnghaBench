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
struct demangle_component {int dummy; } ;
struct d_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 struct demangle_component* d_bare_function_type (struct d_info*,int) ; 
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 char d_peek_char (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_function_type (struct d_info *di)
{
  struct demangle_component *ret;

  if (! d_check_char (di, 'F'))
    return NULL;
  if (d_peek_char (di) == 'Y')
    {
      /* Function has C linkage.  We don't print this information.
	 FIXME: We should print it in verbose mode.  */
      d_advance (di, 1);
    }
  ret = d_bare_function_type (di, 1);
  if (! d_check_char (di, 'E'))
    return NULL;
  return ret;
}