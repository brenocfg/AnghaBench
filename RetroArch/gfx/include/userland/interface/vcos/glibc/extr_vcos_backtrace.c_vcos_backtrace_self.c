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
typedef  int /*<<< orphan*/  stack ;

/* Variables and functions */
 int backtrace (void**,int) ; 
 char** backtrace_symbols (void**,int) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void vcos_backtrace_self(void)
{
#ifdef HAVE_EXECINFO_H
   void *stack[64];
   int depth = backtrace(stack, sizeof(stack)/sizeof(stack[0]));
   char **names = backtrace_symbols(stack, depth);
   int i;
   if (names)
   {
      for (i=0; i<depth; i++)
      {
         printf("%s\n", names[i]);
      }
      free(names);
   }
#endif
}