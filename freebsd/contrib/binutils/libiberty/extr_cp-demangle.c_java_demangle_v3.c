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
 int DMGL_JAVA ; 
 int DMGL_PARAMS ; 
 int DMGL_RET_POSTFIX ; 
 char* d_demangle (char const*,int,size_t*) ; 

char *
java_demangle_v3 (const char *mangled)
{
  size_t alc;

  return d_demangle (mangled, DMGL_JAVA | DMGL_PARAMS | DMGL_RET_POSTFIX, &alc);
}