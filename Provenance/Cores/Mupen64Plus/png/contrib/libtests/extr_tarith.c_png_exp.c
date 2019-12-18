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
typedef  int png_uint_32 ;

/* Variables and functions */
 int LN2 ; 
 int exp (int) ; 
 int /*<<< orphan*/  floor (double) ; 

__attribute__((used)) static png_uint_32 png_exp(png_uint_32 x)
{
   return (png_uint_32)floor(.5 + exp(x * -LN2) * 0xffffffffU);
}