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
struct language_defn {char* (* la_demangle ) (char const*,int) ;} ;

/* Variables and functions */
 char* stub1 (char const*,int) ; 

char *
language_demangle (const struct language_defn *current_language, 
				const char *mangled, int options)
{
  if (current_language != NULL && current_language->la_demangle)
    return current_language->la_demangle (mangled, options);
  return NULL;
}