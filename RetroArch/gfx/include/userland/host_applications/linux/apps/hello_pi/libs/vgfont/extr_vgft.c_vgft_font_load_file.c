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
struct TYPE_3__ {int /*<<< orphan*/  ft_face; } ;
typedef  TYPE_1__ VGFT_FONT_T ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;

/* Variables and functions */
 scalar_t__ FT_New_Face (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  lib ; 

VCOS_STATUS_T vgft_font_load_file(VGFT_FONT_T *font, const char *file)
{
   if (FT_New_Face(lib, file, 0, &font->ft_face)) {
      return VCOS_EINVAL;
   }
   return VCOS_SUCCESS;
}