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
struct display {int dummy; } ;
typedef  int /*<<< orphan*/  png_structp ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ png_get_error_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct display *
get_dp(png_structp pp)
   /* The display pointer is always stored in the png_struct error pointer */
{
   struct display *dp = (struct display*)png_get_error_ptr(pp);

   if (dp == NULL)
   {
      fprintf(stderr, "pngcp: internal error (no display)\n");
      exit(99); /* prevents a crash */
   }

   return dp;
}