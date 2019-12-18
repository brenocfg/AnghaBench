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
typedef  enum languages { ____Placeholder_languages } languages ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  lang_c 130 
#define  lang_cplusplus 129 
#define  lang_java 128 

const char *
language_to_string (enum languages c)
{
  switch (c)
    {
    case lang_c:
      return "C";

    case lang_cplusplus:
      return "C++";

    case lang_java:
      return "Java";

    default:
      gcc_unreachable ();
    }
  return NULL;
}