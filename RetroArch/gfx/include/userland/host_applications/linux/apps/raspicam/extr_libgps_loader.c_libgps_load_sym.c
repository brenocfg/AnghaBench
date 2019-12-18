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
 char* dlerror () ; 
 void* dlsym (void*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int libgps_load_sym(void **func, void *handle, char *symbol)
{
   char *sym_error;

   *func = dlsym(handle, symbol);
   if ((sym_error = dlerror()) != NULL)
   {
      fprintf(stderr, "%s\n", sym_error);
      return -1;
   }
   return 0;
}