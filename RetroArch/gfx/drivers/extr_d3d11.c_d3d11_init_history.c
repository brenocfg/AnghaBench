#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* texture; } ;
struct TYPE_9__ {int init_history; TYPE_2__ frame; int /*<<< orphan*/  device; TYPE_6__* shader_preset; } ;
typedef  TYPE_3__ d3d11_video_t ;
struct TYPE_11__ {scalar_t__ history_size; } ;
struct TYPE_7__ {unsigned int Width; unsigned int Height; int /*<<< orphan*/  Usage; int /*<<< orphan*/  Format; } ;
struct TYPE_10__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_6__*) ; 
 int /*<<< orphan*/  d3d11_init_texture (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void d3d11_init_history(d3d11_video_t* d3d11, unsigned width, unsigned height)
{
   unsigned i;

   /* todo: should we init history to max_width/max_height instead ?
    * to prevent out of memory errors happening several frames later
    * and to reduce memory fragmentation */

   assert(d3d11->shader_preset);
   for (i = 0; i < (unsigned)d3d11->shader_preset->history_size + 1; i++)
   {
      d3d11->frame.texture[i].desc.Width  = width;
      d3d11->frame.texture[i].desc.Height = height;
      d3d11->frame.texture[i].desc.Format = d3d11->frame.texture[0].desc.Format;
      d3d11->frame.texture[i].desc.Usage  = d3d11->frame.texture[0].desc.Usage;
      d3d11_init_texture(d3d11->device, &d3d11->frame.texture[i]);
      /* todo: clear texture ?  */
   }
   d3d11->init_history = false;
}