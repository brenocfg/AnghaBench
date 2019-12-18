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
 char const* gl_locale_name_default () ; 
 char* gl_locale_name_posix (int,char const*) ; 
 char* gl_locale_name_thread (int,char const*) ; 

const char *
gl_locale_name (int category, const char *categoryname)
{
  const char *retval;

  retval = gl_locale_name_thread (category, categoryname);
  if (retval != NULL)
    return retval;

  retval = gl_locale_name_posix (category, categoryname);
  if (retval != NULL)
    return retval;

  return gl_locale_name_default ();
}