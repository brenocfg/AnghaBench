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
struct rtx_iv {scalar_t__ base; scalar_t__ step; scalar_t__ mode; scalar_t__ extend_mode; size_t extend; scalar_t__ mult; scalar_t__ delta; scalar_t__ first_special; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* GET_MODE_NAME (scalar_t__) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const1_rtx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  print_rtl (int /*<<< orphan*/ *,scalar_t__) ; 
 char** rtx_name ; 

void
dump_iv_info (FILE *file, struct rtx_iv *iv)
{
  if (!iv->base)
    {
      fprintf (file, "not simple");
      return;
    }

  if (iv->step == const0_rtx
      && !iv->first_special)
    fprintf (file, "invariant ");

  print_rtl (file, iv->base);
  if (iv->step != const0_rtx)
    {
      fprintf (file, " + ");
      print_rtl (file, iv->step);
      fprintf (file, " * iteration");
    }
  fprintf (file, " (in %s)", GET_MODE_NAME (iv->mode));

  if (iv->mode != iv->extend_mode)
    fprintf (file, " %s to %s",
	     rtx_name[iv->extend],
	     GET_MODE_NAME (iv->extend_mode));

  if (iv->mult != const1_rtx)
    {
      fprintf (file, " * ");
      print_rtl (file, iv->mult);
    }
  if (iv->delta != const0_rtx)
    {
      fprintf (file, " + ");
      print_rtl (file, iv->delta);
    }
  if (iv->first_special)
    fprintf (file, " (first special)");
}