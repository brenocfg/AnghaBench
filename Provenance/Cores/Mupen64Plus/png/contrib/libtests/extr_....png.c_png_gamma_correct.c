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
typedef  int /*<<< orphan*/  png_uint_16 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_fixed_point ;
struct TYPE_3__ {int bit_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_gamma_16bit_correct (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_gamma_8bit_correct (unsigned int,int /*<<< orphan*/ ) ; 

png_uint_16 /* PRIVATE */
png_gamma_correct(png_structrp png_ptr, unsigned int value,
    png_fixed_point gamma_val)
{
   if (png_ptr->bit_depth == 8)
      return png_gamma_8bit_correct(value, gamma_val);

#ifdef PNG_16BIT_SUPPORTED
   else
      return png_gamma_16bit_correct(value, gamma_val);
#else
      /* should not reach this */
      return 0;
#endif /* 16BIT */
}