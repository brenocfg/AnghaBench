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
typedef  int /*<<< orphan*/  uint32_t ;
struct texture_image {int width; unsigned int height; int /*<<< orphan*/ * pixels; } ;
struct d3d8_texture_info {scalar_t__ data; scalar_t__ userdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ d3d8_video_t ;
struct TYPE_5__ {int Pitch; scalar_t__ pBits; } ;
typedef  scalar_t__ LPDIRECT3DTEXTURE8 ;
typedef  TYPE_2__ D3DLOCKED_RECT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DLOCK_NOSYSLOCK ; 
 int /*<<< orphan*/  D3DPOOL_MANAGED ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  d3d8_get_argb8888_format () ; 
 scalar_t__ d3d8_lock_rectangle (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_texture_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  d3d8_unlock_rectangle (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void d3d8_video_texture_load_d3d(
      struct d3d8_texture_info *info,
      uintptr_t *id)
{
   D3DLOCKED_RECT d3dlr;
   unsigned usage           = 0;
   d3d8_video_t *d3d         = (d3d8_video_t*)info->userdata;
   struct texture_image *ti = (struct texture_image*)info->data;
   LPDIRECT3DTEXTURE8 tex   = (LPDIRECT3DTEXTURE8)d3d8_texture_new(d3d->dev, NULL,
               ti->width, ti->height, 0,
               usage, d3d8_get_argb8888_format(),
               D3DPOOL_MANAGED, 0, 0, 0,
               NULL, NULL, false);

   if (!tex)
   {
      RARCH_ERR("[D3D8]: Failed to create texture\n");
      return;
   }

   if (d3d8_lock_rectangle(tex, 0, &d3dlr,
            NULL, 0, D3DLOCK_NOSYSLOCK))
   {
      unsigned i;
      uint32_t       *dst = (uint32_t*)(d3dlr.pBits);
      const uint32_t *src = ti->pixels;
      unsigned      pitch = d3dlr.Pitch >> 2;

      for (i = 0; i < ti->height; i++, dst += pitch, src += ti->width)
         memcpy(dst, src, ti->width << 2);
      d3d8_unlock_rectangle(tex);
   }

   *id = (uintptr_t)tex;
}