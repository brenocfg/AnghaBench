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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ VALUE_HANDLE_EXPR_SET (int /*<<< orphan*/ ) ; 
 int VALUE_HANDLE_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_value_set (int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
print_value_expressions (FILE *outfile, tree val)
{
  if (VALUE_HANDLE_EXPR_SET (val))
    {
      char s[10];
      sprintf (s, "VH.%04d", VALUE_HANDLE_ID (val));
      print_value_set (outfile, VALUE_HANDLE_EXPR_SET (val), s, 0);
    }
}