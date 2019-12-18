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
struct ptr_loc {int lineno; char* filename; } ;

/* Variables and functions */
 struct ptr_loc* get_rtx_ptr_loc (void const*) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 

void
print_rtx_ptr_loc (const void *ptr)
{
  const struct ptr_loc *loc = get_rtx_ptr_loc (ptr);
  if (loc != 0)
    printf ("#line %d \"%s\"\n", loc->lineno, loc->filename);
}