#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  error_color_16; int /*<<< orphan*/  error_gray_16; int /*<<< orphan*/  error_indexed; int /*<<< orphan*/  error_color_8; int /*<<< orphan*/  error_gray_8; int /*<<< orphan*/  error_gray_4; int /*<<< orphan*/  error_gray_2; } ;
typedef  TYPE_1__ png_modifier ;
typedef  char* png_const_charp ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_one (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
summarize_gamma_errors(png_modifier *pm, png_const_charp who, int low_bit_depth,
   int indexed)
{
   fflush(stderr);

   if (who)
      printf("\nGamma correction with %s:\n", who);

   else
      printf("\nBasic gamma correction:\n");

   if (low_bit_depth)
   {
      print_one(" 2 bit gray: ", pm->error_gray_2);
      print_one(" 4 bit gray: ", pm->error_gray_4);
      print_one(" 8 bit gray: ", pm->error_gray_8);
      print_one(" 8 bit color:", pm->error_color_8);
      if (indexed)
         print_one(" indexed:    ", pm->error_indexed);
   }

   print_one("16 bit gray: ", pm->error_gray_16);
   print_one("16 bit color:", pm->error_color_16);

   fflush(stdout);
}