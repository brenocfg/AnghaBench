#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;
typedef  struct TYPE_20__   TYPE_16__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {TYPE_16__* luts; TYPE_10__* shader_preset; TYPE_7__* pass; } ;
typedef  TYPE_8__ wiiu_video_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_25__ {int /*<<< orphan*/  path; } ;
struct video_shader_pass {TYPE_4__ source; } ;
struct texture_image {int width; int height; scalar_t__ pixels; } ;
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_28__ {TYPE_13__* gfd; void** ps_ubos; void** vs_ubos; } ;
struct TYPE_27__ {int uniformBlockCount; TYPE_5__* uniformBlocks; } ;
struct TYPE_26__ {int /*<<< orphan*/  size; } ;
struct TYPE_24__ {int /*<<< orphan*/  path; } ;
struct TYPE_23__ {int uniformBlockCount; TYPE_1__* uniformBlocks; } ;
struct TYPE_22__ {int /*<<< orphan*/  size; } ;
struct TYPE_21__ {int width; int height; int depth; int pitch; int /*<<< orphan*/  imageSize; void* image; int /*<<< orphan*/  alignment; int /*<<< orphan*/  format; int /*<<< orphan*/  tileMode; int /*<<< orphan*/  dim; } ;
struct TYPE_20__ {int viewNumSlices; TYPE_17__ surface; int /*<<< orphan*/  compMap; } ;
struct TYPE_19__ {TYPE_2__* ps; TYPE_6__* vs; } ;
struct TYPE_18__ {unsigned int passes; unsigned int luts; TYPE_3__* lut; struct video_shader_pass* pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  GX2CalcSurfaceSizeAndAlignment (TYPE_17__*) ; 
 int /*<<< orphan*/  GX2DrawDone () ; 
 int /*<<< orphan*/  GX2InitTextureRegs (TYPE_16__*) ; 
 int /*<<< orphan*/  GX2Invalidate (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2_COMP_SEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX2_INVALIDATE_MODE_CPU_TEXTURE ; 
 int /*<<< orphan*/  GX2_INVALIDATE_MODE_CPU_UNIFORM_BLOCK ; 
 int /*<<< orphan*/  GX2_SURFACE_DIM_TEXTURE_2D ; 
 int /*<<< orphan*/  GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8 ; 
 int /*<<< orphan*/  GX2_TILE_MODE_LINEAR_ALIGNED ; 
 int /*<<< orphan*/  GX2_UNIFORM_BLOCK_ALIGNMENT ; 
 void* MEM2_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PATH_MAX_LENGTH ; 
 int RARCH_SHADER_SLANG ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  _A ; 
 int /*<<< orphan*/  _B ; 
 int /*<<< orphan*/  _G ; 
 int /*<<< orphan*/  _R ; 
 TYPE_10__* calloc (int,int) ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_10__*) ; 
 TYPE_13__* gfd_open (char*) ; 
 int /*<<< orphan*/  image_texture_free (struct texture_image*) ; 
 scalar_t__ image_texture_load (struct texture_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slang_preprocess_parse_parameters (int /*<<< orphan*/ ,TYPE_10__*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  video_shader_read_conf_preset (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/ * video_shader_read_preset (char const*) ; 
 int /*<<< orphan*/  video_shader_resolve_current_parameters (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  wiiu_free_shader_preset (TYPE_8__*) ; 

__attribute__((used)) static bool wiiu_gfx_set_shader(void *data,
      enum rarch_shader_type type, const char *path)
{
   unsigned i;
   config_file_t *conf = NULL;
   wiiu_video_t *wiiu  = (wiiu_video_t *)data;

   if (!wiiu)
      return false;

   GX2DrawDone();
   wiiu_free_shader_preset(wiiu);

   if (string_is_empty(path))
      return true;

   if (type != RARCH_SHADER_SLANG)
   {
      RARCH_WARN("[GX2] Only Slang shaders are supported. Falling back to stock.\n");
      return false;
   }

   if (!(conf = video_shader_read_preset(path)))
      return false;

   wiiu->shader_preset = calloc(1, sizeof(*wiiu->shader_preset));

   if (!video_shader_read_conf_preset(conf, wiiu->shader_preset))
   {
      free(wiiu->shader_preset);
      wiiu->shader_preset = NULL;
      return false;
   }

   for (i = 0; i < wiiu->shader_preset->passes; i++)
       slang_preprocess_parse_parameters(wiiu->shader_preset->pass[i].source.path, wiiu->shader_preset);

   video_shader_resolve_current_parameters(conf, wiiu->shader_preset);
   config_file_free(conf);

   for (i = 0; i < wiiu->shader_preset->passes; i++)
   {
      char gfdpath[PATH_MAX_LENGTH];
      struct video_shader_pass *pass = &wiiu->shader_preset->pass[i];

      strncpy(gfdpath, pass->source.path, PATH_MAX_LENGTH);

      char *ptr = strrchr(gfdpath, '.');

      if (!ptr)
         ptr = gfdpath + strlen(gfdpath);

      *ptr++ = '.';
      *ptr++ = 'g';
      *ptr++ = 's';
      *ptr++ = 'h';
      *ptr++ = '\0';

      wiiu->pass[i].gfd = gfd_open(gfdpath);

      if (!wiiu->pass[i].gfd)
      {
         wiiu_free_shader_preset(wiiu);
         return false;
      }

      for (int j = 0; j < 2 && j < wiiu->pass[i].gfd->vs->uniformBlockCount; j++)
      {
         wiiu->pass[i].vs_ubos[j] = MEM2_alloc(wiiu->pass[i].gfd->vs->uniformBlocks[j].size,
                                               GX2_UNIFORM_BLOCK_ALIGNMENT);
         memset(wiiu->pass[i].vs_ubos[j], 0, wiiu->pass[i].gfd->vs->uniformBlocks[j].size);
         GX2Invalidate(GX2_INVALIDATE_MODE_CPU_UNIFORM_BLOCK, wiiu->pass[i].vs_ubos[j],
                       wiiu->pass[i].gfd->vs->uniformBlocks[j].size);
      }

      for (int j = 0; j < 2 && j < wiiu->pass[i].gfd->ps->uniformBlockCount; j++)
      {
         wiiu->pass[i].ps_ubos[j] = MEM2_alloc(wiiu->pass[i].gfd->ps->uniformBlocks[j].size,
                                               GX2_UNIFORM_BLOCK_ALIGNMENT);
         memset(wiiu->pass[i].ps_ubos[j], 0, wiiu->pass[i].gfd->ps->uniformBlocks[j].size);
         GX2Invalidate(GX2_INVALIDATE_MODE_CPU_UNIFORM_BLOCK, wiiu->pass[i].ps_ubos[j],
                       wiiu->pass[i].gfd->ps->uniformBlocks[j].size);
      }
   }

   for (i = 0; i < wiiu->shader_preset->luts; i++)
   {
      struct texture_image image = {};

      if (image_texture_load(&image, wiiu->shader_preset->lut[i].path))
      {
         wiiu->luts[i].surface.width       = image.width;
         wiiu->luts[i].surface.height      = image.height;
         wiiu->luts[i].surface.depth       = 1;
         wiiu->luts[i].surface.dim         = GX2_SURFACE_DIM_TEXTURE_2D;
         wiiu->luts[i].surface.tileMode    = GX2_TILE_MODE_LINEAR_ALIGNED;
         wiiu->luts[i].viewNumSlices       = 1;

         wiiu->luts[i].surface.format      = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;
         wiiu->luts[i].compMap             = GX2_COMP_SEL(_G, _B, _A, _R);

         GX2CalcSurfaceSizeAndAlignment(&wiiu->luts[i].surface);
         GX2InitTextureRegs(&wiiu->luts[i]);
         wiiu->luts[i].surface.image = MEM2_alloc(wiiu->luts[i].surface.imageSize,
                                       wiiu->luts[i].surface.alignment);

         for (int j = 0; (j < image.height) && (j < wiiu->luts[i].surface.height); j++)
            memcpy((uint32_t *)wiiu->luts[i].surface.image + (j * wiiu->luts[i].surface.pitch),
                   image.pixels + (j * image.width), image.width * sizeof(image.pixels));

         GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, wiiu->luts[i].surface.image,
                       wiiu->luts[i].surface.imageSize);

         image_texture_free(&image);
      }
   }

   return true;
}