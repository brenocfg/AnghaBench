#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  font; } ;
typedef  TYPE_1__ d3dfonts_t ;
struct TYPE_5__ {int right; int left; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ RECT ;

/* Variables and functions */
 int /*<<< orphan*/  DT_CALCRECT ; 
 int /*<<< orphan*/  d3d9x_font_draw_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,unsigned int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int d3dfonts_w32_get_message_width(void* data, const char* msg,
      unsigned msg_len, float scale)
{
   RECT box             = {0,0,0,0};
   d3dfonts_t *d3dfonts = (d3dfonts_t*)data;

   if (!d3dfonts || !msg)
      return 0;

   d3d9x_font_draw_text(d3dfonts->font, NULL, (void*)msg,
         msg_len? msg_len : -1, &box, DT_CALCRECT, 0);

   return box.right - box.left;
}