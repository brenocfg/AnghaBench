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
typedef  float VGfloat ;
typedef  scalar_t__ FT_Pos ;

/* Variables and functions */

__attribute__((used)) static VGfloat float_from_26_6(FT_Pos x)
{
   return (VGfloat)x / 64.0f;
}