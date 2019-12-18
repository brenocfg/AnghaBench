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
struct TYPE_3__ {scalar_t__ vg_font; int /*<<< orphan*/ * ft_face; } ;
typedef  TYPE_1__ VGFT_FONT_T ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_ENOMEM ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 scalar_t__ VG_INVALID_HANDLE ; 
 scalar_t__ vgCreateFont (int /*<<< orphan*/ ) ; 

VCOS_STATUS_T vgft_font_init(VGFT_FONT_T *font)
{
   font->ft_face = NULL;
   font->vg_font = vgCreateFont(0);
   if (font->vg_font == VG_INVALID_HANDLE)
   {
      return VCOS_ENOMEM;
   }
   return VCOS_SUCCESS;
}