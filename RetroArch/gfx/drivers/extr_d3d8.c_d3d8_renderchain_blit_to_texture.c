#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int last_width; unsigned int last_height; int /*<<< orphan*/  tex; int /*<<< orphan*/  pixel_size; int /*<<< orphan*/  tex_h; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ d3d8_renderchain_t ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE8 ;
typedef  int /*<<< orphan*/  D3DLOCKED_RECT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DLOCK_NOSYSLOCK ; 
 int /*<<< orphan*/  d3d8_frame_postprocess (TYPE_1__*) ; 
 scalar_t__ d3d8_lock_rectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_lock_rectangle_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3d8_texture_blit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void const*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  d3d8_unlock_rectangle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d3d8_renderchain_blit_to_texture(
      d3d8_renderchain_t *chain,
      const void *frame,
      unsigned width, unsigned height, unsigned pitch)
{
   D3DLOCKED_RECT d3dlr;
   LPDIRECT3DDEVICE8 d3dr     = (LPDIRECT3DDEVICE8)chain->dev;

   d3d8_frame_postprocess(chain);

   if (chain->last_width != width || chain->last_height != height)
   {
      d3d8_lock_rectangle(chain->tex,
            0, &d3dlr, NULL, chain->tex_h, D3DLOCK_NOSYSLOCK);
      d3d8_lock_rectangle_clear(chain->tex,
            0, &d3dlr, NULL, chain->tex_h, D3DLOCK_NOSYSLOCK);
   }

   /* Set the texture to NULL so D3D doesn't complain about it being in use... */
   d3d8_set_texture(d3dr, 0, NULL);

   if (d3d8_lock_rectangle(chain->tex, 0, &d3dlr, NULL, 0, 0))
   {
      d3d8_texture_blit(chain->pixel_size, chain->tex,
            &d3dlr, frame, width, height, pitch);
      d3d8_unlock_rectangle(chain->tex);
   }
}