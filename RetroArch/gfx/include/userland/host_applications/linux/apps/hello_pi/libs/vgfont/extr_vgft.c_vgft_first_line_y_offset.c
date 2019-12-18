#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VGfloat ;
struct TYPE_9__ {TYPE_3__* ft_face; } ;
typedef  TYPE_4__ VGFT_FONT_T ;
struct TYPE_8__ {TYPE_2__* size; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; } ;
struct TYPE_7__ {TYPE_1__ metrics; } ;

/* Variables and functions */
 int /*<<< orphan*/  float_from_26_6 (int /*<<< orphan*/ ) ; 

VGfloat vgft_first_line_y_offset(VGFT_FONT_T *font) {
   return float_from_26_6(font->ft_face->size->metrics.height);
}