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
typedef  int ptrdiff_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memcpy (char**,char const**,int) ; 
 int /*<<< orphan*/  memmove (char**,char**,int) ; 
 int /*<<< orphan*/  retro_assert (char const**) ; 

__attribute__((used)) static void shuffle_block(char **begin, char **last, char **end)
{
   ptrdiff_t    len = last - begin;
   const char **tmp = (const char**)calloc(len, sizeof(const char*));

   retro_assert(tmp);

   memcpy((void*)tmp, begin, len * sizeof(const char*));
   memmove(begin, last, (end - last) * sizeof(const char*));
   memcpy(end - len, tmp, len * sizeof(const char*));

   free((void*)tmp);
}