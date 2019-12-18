#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* texture; } ;
struct TYPE_9__ {int /*<<< orphan*/  srv_heap; } ;
struct TYPE_11__ {int init_history; TYPE_3__ frame; int /*<<< orphan*/  device; TYPE_2__ desc; TYPE_7__* shader_preset; } ;
typedef  TYPE_4__ d3d12_video_t ;
struct TYPE_13__ {scalar_t__ history_size; } ;
struct TYPE_8__ {unsigned int Width; unsigned int Height; int /*<<< orphan*/  MipLevels; int /*<<< orphan*/  Format; } ;
struct TYPE_12__ {int /*<<< orphan*/ * srv_heap; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_7__*) ; 
 int /*<<< orphan*/  d3d12_init_texture (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void d3d12_init_history(d3d12_video_t* d3d12, unsigned width, unsigned height)
{
   unsigned i;

   /* todo: should we init history to max_width/max_height instead ?
    * to prevent out of memory errors happening several frames later
    * and to reduce memory fragmentation */

   assert(d3d12->shader_preset);
   for (i = 0; i < (unsigned)d3d12->shader_preset->history_size + 1; i++)
   {
      d3d12->frame.texture[i].desc.Width     = width;
      d3d12->frame.texture[i].desc.Height    = height;
      d3d12->frame.texture[i].desc.Format    = d3d12->frame.texture[0].desc.Format;
      d3d12->frame.texture[i].desc.MipLevels = d3d12->frame.texture[0].desc.MipLevels;
      d3d12->frame.texture[i].srv_heap       = &d3d12->desc.srv_heap;
      d3d12_init_texture(d3d12->device, &d3d12->frame.texture[i]);
      /* todo: clear texture ?  */
   }
   d3d12->init_history = false;
}