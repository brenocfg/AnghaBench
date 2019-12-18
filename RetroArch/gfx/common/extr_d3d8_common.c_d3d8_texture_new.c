#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct IDirect3DTexture8 {int dummy; } ;
typedef  int /*<<< orphan*/  PALETTEENTRY ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE8 ;
typedef  scalar_t__ INT32 ;
typedef  int /*<<< orphan*/  D3DPOOL ;
typedef  int /*<<< orphan*/  D3DFORMAT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice8_CreateTexture (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct IDirect3DTexture8**) ; 
 int /*<<< orphan*/  _dev ; 
 void* d3d8_texture_new_from_file (int /*<<< orphan*/ ,char const*,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,scalar_t__,void*,int /*<<< orphan*/ *) ; 

void *d3d8_texture_new(LPDIRECT3DDEVICE8 dev,
      const char *path, unsigned width, unsigned height,
      unsigned miplevels, unsigned usage, INT32 format,
      INT32 pool, unsigned filter, unsigned mipfilter,
      INT32 color_key, void *src_info_data,
      PALETTEENTRY *palette, bool want_mipmap)
{
   void *buf             = NULL;

   if (path)
   {
#ifdef HAVE_D3DX
      return d3d8_texture_new_from_file(_dev,
            path, width, height, miplevels,
            usage, (D3DFORMAT)format,
            (D3DPOOL)pool, filter, mipfilter,
            color_key, src_info_data, palette);
#else
      return NULL;
#endif
   }

   if (FAILED(IDirect3DDevice8_CreateTexture(dev,
               width, height, miplevels, usage,
               (D3DFORMAT)format, (D3DPOOL)pool,
               (struct IDirect3DTexture8**)&buf)))
      return NULL;

   return buf;
}