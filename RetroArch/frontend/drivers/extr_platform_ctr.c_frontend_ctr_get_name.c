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
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void frontend_ctr_get_name(char* s, size_t len)
{
   u8 device_model = 0xFF;
   
   /*(0 = O3DS, 1 = O3DSXL, 2 = N3DS, 3 = 2DS, 4 = N3DSXL, 5 = N2DSXL)*/
   CFGU_GetSystemModel(&device_model);

   switch (device_model)
   {
      case 0:
         strlcpy(s, "Old 3DS", len);
         break;
      case 1:
         strlcpy(s, "Old 3DS XL", len);
         break;
      case 2:
         strlcpy(s, "New 3DS", len);
         break;
      case 3:
         strlcpy(s, "Old 2DS", len);
         break;
      case 4:
         strlcpy(s, "New 3DS XL", len);
         break;
      case 5:
         strlcpy(s, "New 2DS XL", len);
         break;

      default:
         strlcpy(s, "Unknown Device", len);
         break;
   }
}