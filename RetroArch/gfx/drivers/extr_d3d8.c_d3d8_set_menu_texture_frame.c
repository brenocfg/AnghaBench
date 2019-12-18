#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_6__ {TYPE_1__* menu; int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ d3d8_video_t ;
struct TYPE_7__ {int Pitch; scalar_t__ pBits; } ;
struct TYPE_5__ {unsigned int tex_w; unsigned int tex_h; unsigned int* tex_coords; float alpha_mod; scalar_t__ tex; } ;
typedef  TYPE_3__ D3DLOCKED_RECT ;

/* Variables and functions */
 int /*<<< orphan*/  D3DLOCK_NOSYSLOCK ; 
 int /*<<< orphan*/  D3DPOOL_MANAGED ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  d3d8_get_argb8888_format () ; 
 scalar_t__ d3d8_lock_rectangle (scalar_t__,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_texture_free (scalar_t__) ; 
 scalar_t__ d3d8_texture_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  d3d8_unlock_rectangle (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void d3d8_set_menu_texture_frame(void *data,
      const void *frame, bool rgb32, unsigned width, unsigned height,
      float alpha)
{
   D3DLOCKED_RECT d3dlr;
   d3d8_video_t *d3d = (d3d8_video_t*)data;

   (void)d3dlr;
   (void)frame;
   (void)rgb32;
   (void)width;
   (void)height;
   (void)alpha;

   if (    !d3d->menu->tex            ||
            d3d->menu->tex_w != width ||
            d3d->menu->tex_h != height)
   {
      if (d3d->menu)
	     d3d8_texture_free(d3d->menu->tex);

      d3d->menu->tex = d3d8_texture_new(d3d->dev, NULL,
            width, height, 1,
            0, d3d8_get_argb8888_format(),
            D3DPOOL_MANAGED, 0, 0, 0, NULL, NULL, false);

      if (!d3d->menu->tex)
      {
         RARCH_ERR("[D3D8]: Failed to create menu texture.\n");
         return;
      }

      d3d->menu->tex_w          = width;
      d3d->menu->tex_h          = height;
#ifdef _XBOX
      d3d->menu->tex_coords [2] = width;
      d3d->menu->tex_coords[3]  = height;
#endif
   }

   d3d->menu->alpha_mod = alpha;

   if (d3d8_lock_rectangle(d3d->menu->tex, 0, &d3dlr,
            NULL, 0, D3DLOCK_NOSYSLOCK))
   {
      unsigned h, w;
      if (rgb32)
      {
         uint8_t        *dst = (uint8_t*)d3dlr.pBits;
         const uint32_t *src = (const uint32_t*)frame;

         for (h = 0; h < height; h++, dst += d3dlr.Pitch, src += width)
         {
            memcpy(dst, src, width * sizeof(uint32_t));
            memset(dst + width * sizeof(uint32_t), 0,
                  d3dlr.Pitch - width * sizeof(uint32_t));
         }
      }
      else
      {
         uint32_t       *dst = (uint32_t*)d3dlr.pBits;
         const uint16_t *src = (const uint16_t*)frame;

         for (h = 0; h < height; h++, dst += d3dlr.Pitch >> 2, src += width)
         {
            for (w = 0; w < width; w++)
            {
               uint16_t c = src[w];
               uint32_t r = (c >> 12) & 0xf;
               uint32_t g = (c >>  8) & 0xf;
               uint32_t b = (c >>  4) & 0xf;
               uint32_t a = (c >>  0) & 0xf;
               r          = ((r << 4) | r) << 16;
               g          = ((g << 4) | g) <<  8;
               b          = ((b << 4) | b) <<  0;
               a          = ((a << 4) | a) << 24;
               dst[w]     = r | g | b | a;
            }
         }
      }

      if (d3d->menu)
         d3d8_unlock_rectangle(d3d->menu->tex);
   }
}