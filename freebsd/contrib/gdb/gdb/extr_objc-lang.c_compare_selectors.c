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
struct symbol {int dummy; } ;

/* Variables and functions */
 char* SYMBOL_PRINT_NAME (struct symbol*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int specialcmp (char*,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
compare_selectors (const void *a, const void *b)
{
  char *aname, *bname;

  aname = SYMBOL_PRINT_NAME (*(struct symbol **) a);
  bname = SYMBOL_PRINT_NAME (*(struct symbol **) b);
  if (aname == NULL || bname == NULL)
    error ("internal: compare_selectors(1)");

  aname = strchr(aname, ' ');
  bname = strchr(bname, ' ');
  if (aname == NULL || bname == NULL)
    error ("internal: compare_selectors(2)");

  return specialcmp (aname+1, bname+1);
}