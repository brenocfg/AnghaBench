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
typedef  enum menu_display_prim_type { ____Placeholder_menu_display_prim_type } menu_display_prim_type ;
typedef  int /*<<< orphan*/  INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  D3DPT_COMM_TRIANGLESTRIP ; 
#define  MENU_DISPLAY_PRIM_NONE 130 
#define  MENU_DISPLAY_PRIM_TRIANGLES 129 
#define  MENU_DISPLAY_PRIM_TRIANGLESTRIP 128 

__attribute__((used)) static INT32 menu_display_prim_to_d3d9_enum(
      enum menu_display_prim_type prim_type)
{
   switch (prim_type)
   {
      case MENU_DISPLAY_PRIM_TRIANGLES:
      case MENU_DISPLAY_PRIM_TRIANGLESTRIP:
         return D3DPT_COMM_TRIANGLESTRIP;
      case MENU_DISPLAY_PRIM_NONE:
      default:
         break;
   }

   /* TOD/FIXME - hack */
   return 0;
}