#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * ps2_video; int /*<<< orphan*/  gsFontM; } ;
typedef  TYPE_1__ ps2_font_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  deinit_gsfont (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps2_font_free_font(void *data, bool is_threaded)
{
   ps2_font_info_t *ps2 = (ps2_font_info_t *)data;
   deinit_gsfont(ps2->gsFontM);
   ps2->ps2_video = NULL;
   ps2 = NULL;
}