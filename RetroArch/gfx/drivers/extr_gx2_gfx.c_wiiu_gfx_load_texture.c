#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wiiu_video_t ;
typedef  int uint32_t ;
struct texture_image {int width; int height; scalar_t__ pixels; } ;
typedef  enum texture_filter_type { ____Placeholder_texture_filter_type } texture_filter_type ;
struct TYPE_6__ {int width; int height; int depth; int pitch; int /*<<< orphan*/  imageSize; scalar_t__ image; int /*<<< orphan*/  alignment; int /*<<< orphan*/  format; int /*<<< orphan*/  tileMode; int /*<<< orphan*/  dim; } ;
struct TYPE_5__ {int viewNumSlices; TYPE_4__ surface; int /*<<< orphan*/  compMap; } ;
typedef  TYPE_1__ GX2Texture ;

/* Variables and functions */
 int /*<<< orphan*/  GX2CalcSurfaceSizeAndAlignment (TYPE_4__*) ; 
 int /*<<< orphan*/  GX2InitTextureRegs (TYPE_1__*) ; 
 int /*<<< orphan*/  GX2Invalidate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2_COMP_SEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2_INVALIDATE_MODE_CPU_TEXTURE ; 
 int /*<<< orphan*/  GX2_SURFACE_DIM_TEXTURE_2D ; 
 int /*<<< orphan*/  GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8 ; 
 int /*<<< orphan*/  GX2_TILE_MODE_LINEAR_ALIGNED ; 
 scalar_t__ MEM2_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _A ; 
 int /*<<< orphan*/  _B ; 
 int /*<<< orphan*/  _G ; 
 int /*<<< orphan*/  _R ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__,int) ; 

__attribute__((used)) static uintptr_t wiiu_gfx_load_texture(void *video_data, void *data,
                                       bool threaded, enum texture_filter_type filter_type)
{
   uint32_t i;
   wiiu_video_t *wiiu = (wiiu_video_t *) video_data;
   struct texture_image *image = (struct texture_image *)data;

   if (!wiiu)
      return 0;

   GX2Texture *texture = calloc(1, sizeof(GX2Texture));

   texture->surface.width       = image->width;
   texture->surface.height      = image->height;
   texture->surface.depth       = 1;
   texture->surface.dim         = GX2_SURFACE_DIM_TEXTURE_2D;
   texture->surface.tileMode    = GX2_TILE_MODE_LINEAR_ALIGNED;
   texture->viewNumSlices       = 1;

   texture->surface.format      = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;
   texture->compMap             = GX2_COMP_SEL(_G, _B, _A, _R);

   GX2CalcSurfaceSizeAndAlignment(&texture->surface);
   GX2InitTextureRegs(texture);
   texture->surface.image = MEM2_alloc(texture->surface.imageSize, texture->surface.alignment);

   for (i = 0; (i < image->height) && (i < texture->surface.height); i++)
      memcpy((uint32_t *)texture->surface.image + (i * texture->surface.pitch),
             image->pixels + (i * image->width), image->width * sizeof(image->pixels));

   GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, texture->surface.image, texture->surface.imageSize);

   return (uintptr_t)texture;
}