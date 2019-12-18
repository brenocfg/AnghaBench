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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  ada_print_scalar (struct type*,int /*<<< orphan*/ ,struct ui_file*) ; 
 scalar_t__ ada_scan_number (char*,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,int,char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
print_range_bound (struct type *type, char *bounds, int *n,
		   struct ui_file *stream)
{
  LONGEST B;
  if (ada_scan_number (bounds, *n, &B, n))
    {
      ada_print_scalar (type, B, stream);
      if (bounds[*n] == '_')
	*n += 2;
    }
  else
    {
      int bound_len;
      char *bound = bounds + *n;
      char *pend;

      pend = strstr (bound, "__");
      if (pend == NULL)
	*n += bound_len = strlen (bound);
      else
	{
	  bound_len = pend - bound;
	  *n += bound_len + 2;
	}
      fprintf_filtered (stream, "%.*s", bound_len, bound);
    }
}