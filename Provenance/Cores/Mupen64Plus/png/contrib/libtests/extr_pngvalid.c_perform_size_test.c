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
typedef  int /*<<< orphan*/  png_modifier ;

/* Variables and functions */
 int READ_BDHI ; 
 int /*<<< orphan*/  test_size (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void
perform_size_test(png_modifier *pm)
{
   /* Test each colour type over the valid range of bit depths (expressed as
    * log2(bit_depth) in turn, stop as soon as any error is detected.
    */
   if (!test_size(pm, 0, 0, READ_BDHI))
      return;

   if (!test_size(pm, 2, 3, READ_BDHI))
      return;

   /* For the moment don't do the palette test - it's a waste of time when
    * compared to the grayscale test.
    */
#if 0
   if (!test_size(pm, 3, 0, 3))
      return;
#endif

   if (!test_size(pm, 4, 3, READ_BDHI))
      return;

   if (!test_size(pm, 6, 3, READ_BDHI))
      return;
}