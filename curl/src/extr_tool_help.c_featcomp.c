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
 int strcasecmp (char* const,char* const) ; 
 int strcmp (char* const,char* const) ; 
 int strcmpi (char* const,char* const) ; 

__attribute__((used)) static int
featcomp(const void *p1, const void *p2)
{
  /* The arguments to this function are "pointers to pointers to char", but
     the comparison arguments are "pointers to char", hence the following cast
     plus dereference */
#ifdef HAVE_STRCASECMP
  return strcasecmp(* (char * const *) p1, * (char * const *) p2);
#elif defined(HAVE_STRCMPI)
  return strcmpi(* (char * const *) p1, * (char * const *) p2);
#else
  return strcmp(* (char * const *) p1, * (char * const *) p2);
#endif
}