#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* face; } ;
typedef  TYPE_4__ ft_font_renderer_t ;
struct TYPE_7__ {TYPE_2__* size; } ;
struct TYPE_5__ {int height; } ;
struct TYPE_6__ {TYPE_1__ metrics; } ;

/* Variables and functions */

__attribute__((used)) static int font_renderer_ft_get_line_height(void* data)
{
   ft_font_renderer_t *handle = (ft_font_renderer_t*)data;
   if (!handle || !handle->face)
      return 0;
   return handle->face->size->metrics.height/64;
}