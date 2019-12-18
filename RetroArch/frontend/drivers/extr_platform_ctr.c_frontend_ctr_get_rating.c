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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CFGU_GetSystemModel (int*) ; 

__attribute__((used)) static int frontend_ctr_get_rating(void)
{
   u8 device_model = 0xFF;
   
   /*(0 = O3DS, 1 = O3DSXL, 2 = N3DS, 3 = 2DS, 4 = N3DSXL, 5 = N2DSXL)*/
   CFGU_GetSystemModel(&device_model);

   switch (device_model)
   {
      case 0:
      case 1:
      case 3:
         /*Old 3/2DS*/
         return 3;
      case 2:
      case 4:
      case 5:
         /*New 3/2DS*/
         return 6;
      default:
         /*Unknown Device Or Check Failed*/
         break;
   }

   return -1;
}