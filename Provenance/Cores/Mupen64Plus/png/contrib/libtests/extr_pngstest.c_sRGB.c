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
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int sRGB_from_linear (double) ; 
 int /*<<< orphan*/  u8d (int) ; 

__attribute__((used)) static png_byte
sRGB(double linear /*range 0.0 .. 1.0*/)
{
   return u8d(255 * sRGB_from_linear(linear));
}