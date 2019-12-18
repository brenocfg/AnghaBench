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
typedef  int /*<<< orphan*/  png_const_structp ;

/* Variables and functions */
#define  PNG_INTERLACE_ADAM7 129 
 int PNG_INTERLACE_ADAM7_PASSES ; 
#define  PNG_INTERLACE_NONE 128 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
npasses_from_interlace_type(png_const_structp pp, int interlace_type)
{
   switch (interlace_type)
   {
   default:
      png_error(pp, "invalid interlace type");

   case PNG_INTERLACE_NONE:
      return 1;

   case PNG_INTERLACE_ADAM7:
      return PNG_INTERLACE_ADAM7_PASSES;
   }
}