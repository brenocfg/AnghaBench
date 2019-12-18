#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  chroma_v_index; int /*<<< orphan*/  chroma_u_index; int /*<<< orphan*/ * luma_index; int /*<<< orphan*/  render_func; int /*<<< orphan*/  fourcc; } ;
typedef  TYPE_1__ xv_t ;
struct TYPE_11__ {scalar_t__ rgb32; } ;
typedef  TYPE_2__ video_info_t ;
typedef  int /*<<< orphan*/  XvPortID ;
struct TYPE_12__ {scalar_t__ type; int bits_per_pixel; scalar_t__ format; scalar_t__* component_order; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ XvImageFormatValues ;
struct TYPE_13__ {scalar_t__* components; int /*<<< orphan*/  v_index; int /*<<< orphan*/  u_index; int /*<<< orphan*/ * luma_index; int /*<<< orphan*/  render_16; int /*<<< orphan*/  render_32; } ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_6__*) ; 
 int /*<<< orphan*/  XFree (TYPE_3__*) ; 
 TYPE_3__* XvListImageFormats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ XvPacked ; 
 scalar_t__ XvYUV ; 
 TYPE_6__* formats ; 
 int /*<<< orphan*/  g_x11_dpy ; 

__attribute__((used)) static bool xv_adaptor_set_format(xv_t *xv, Display *dpy,
      XvPortID port, const video_info_t *video)
{
   int i;
   unsigned j;
   int format_count;
   XvImageFormatValues *format = XvListImageFormats(
         g_x11_dpy, port, &format_count);

   if (!format)
      return false;

   for (i = 0; i < format_count; i++)
   {
      for (j = 0; j < ARRAY_SIZE(formats); j++)
      {
         if (format[i].type == XvYUV
               && format[i].bits_per_pixel == 16
               && format[i].format == XvPacked)
         {
            if (format[i].component_order[0] == formats[j].components[0] &&
                  format[i].component_order[1] == formats[j].components[1] &&
                  format[i].component_order[2] == formats[j].components[2] &&
                  format[i].component_order[3] == formats[j].components[3])
            {
               xv->fourcc         = format[i].id;
               xv->render_func    = video->rgb32
                  ? formats[j].render_32 : formats[j].render_16;

               xv->luma_index[0]  = formats[j].luma_index[0];
               xv->luma_index[1]  = formats[j].luma_index[1];
               xv->chroma_u_index = formats[j].u_index;
               xv->chroma_v_index = formats[j].v_index;
               XFree(format);
               return true;
            }
         }
      }
   }

   XFree(format);
   return false;
}