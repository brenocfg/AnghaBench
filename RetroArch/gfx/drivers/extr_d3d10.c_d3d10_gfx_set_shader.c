#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_56__   TYPE_9__ ;
typedef  struct TYPE_55__   TYPE_8__ ;
typedef  struct TYPE_54__   TYPE_7__ ;
typedef  struct TYPE_53__   TYPE_6__ ;
typedef  struct TYPE_52__   TYPE_5__ ;
typedef  struct TYPE_51__   TYPE_4__ ;
typedef  struct TYPE_50__   TYPE_3__ ;
typedef  struct TYPE_49__   TYPE_2__ ;
typedef  struct TYPE_48__   TYPE_28__ ;
typedef  struct TYPE_47__   TYPE_25__ ;
typedef  struct TYPE_46__   TYPE_24__ ;
typedef  struct TYPE_45__   TYPE_22__ ;
typedef  struct TYPE_44__   TYPE_21__ ;
typedef  struct TYPE_43__   TYPE_20__ ;
typedef  struct TYPE_42__   TYPE_1__ ;
typedef  struct TYPE_41__   TYPE_19__ ;
typedef  struct TYPE_40__   TYPE_18__ ;
typedef  struct TYPE_39__   TYPE_17__ ;
typedef  struct TYPE_38__   TYPE_16__ ;
typedef  struct TYPE_37__   TYPE_15__ ;
typedef  struct TYPE_36__   TYPE_14__ ;
typedef  struct TYPE_35__   TYPE_13__ ;
typedef  struct TYPE_34__   TYPE_12__ ;
typedef  struct TYPE_33__   TYPE_11__ ;
typedef  struct TYPE_32__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vs_path ;
struct video_shader {unsigned int passes; unsigned int luts; TYPE_14__* lut; TYPE_12__* pass; } ;
struct texture_image {int supports_rgba; int /*<<< orphan*/  pixels; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  member_0; } ;
struct TYPE_56__ {int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_55__ {int member_1; int member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_0; } ;
struct TYPE_53__ {int member_1; int member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_0; } ;
struct TYPE_52__ {int member_1; int member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_0; } ;
struct TYPE_51__ {int member_1; int member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_0; } ;
struct TYPE_50__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_49__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_42__ {TYPE_8__ member_5; TYPE_6__ member_4; TYPE_5__ member_3; TYPE_4__ member_2; TYPE_3__ member_1; TYPE_2__ member_0; } ;
struct TYPE_40__ {TYPE_9__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_18__ semantics_map_t ;
typedef  int /*<<< orphan*/  ps_path ;
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;
struct TYPE_38__ {int /*<<< orphan*/  output_size; TYPE_20__* texture; } ;
struct TYPE_41__ {int resize_render_targets; int init_history; struct video_shader* shader_preset; TYPE_25__* luts; int /*<<< orphan*/  device; TYPE_17__* pass; TYPE_16__ frame; int /*<<< orphan*/  mvp; } ;
typedef  TYPE_19__ d3d10_video_t ;
struct TYPE_43__ {int /*<<< orphan*/  size_data; int /*<<< orphan*/  view; } ;
typedef  TYPE_20__ d3d10_texture_t ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_54__ {int /*<<< orphan*/  size_data; int /*<<< orphan*/  view; } ;
struct TYPE_48__ {int /*<<< orphan*/  ps; int /*<<< orphan*/  vs; } ;
struct TYPE_37__ {int /*<<< orphan*/  MiscFlags; int /*<<< orphan*/  Format; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; } ;
struct TYPE_47__ {TYPE_15__ desc; int /*<<< orphan*/  size_data; int /*<<< orphan*/  view; } ;
struct TYPE_46__ {TYPE_13__* cbuffers; } ;
struct TYPE_45__ {int /*<<< orphan*/  ByteWidth; scalar_t__ MiscFlags; int /*<<< orphan*/  CPUAccessFlags; int /*<<< orphan*/  BindFlags; int /*<<< orphan*/  Usage; } ;
struct TYPE_44__ {char* member_0; int member_1; int /*<<< orphan*/  member_6; int /*<<< orphan*/  const member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  const member_2; } ;
struct TYPE_39__ {int /*<<< orphan*/ * buffers; TYPE_24__ semantics; TYPE_28__ shader; int /*<<< orphan*/  frame_direction; int /*<<< orphan*/  frame_count; TYPE_20__ rt; TYPE_7__ feedback; } ;
struct TYPE_36__ {scalar_t__ mipmap; int /*<<< orphan*/  path; } ;
struct TYPE_35__ {int /*<<< orphan*/  size; } ;
struct TYPE_32__ {char* vertex; char* fragment; } ;
struct TYPE_33__ {char* path; TYPE_10__ string; } ;
struct TYPE_34__ {TYPE_11__ source; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_21__ D3D10_INPUT_ELEMENT_DESC ;
typedef  TYPE_22__ D3D10_BUFFER_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  D3D10CreateBuffer (int /*<<< orphan*/ ,TYPE_22__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D10Flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D10_BIND_CONSTANT_BUFFER ; 
 int /*<<< orphan*/  D3D10_CPU_ACCESS_WRITE ; 
#define  D3D10_INPUT_PER_VERTEX_DATA 132 
 int /*<<< orphan*/  D3D10_RESOURCE_MISC_GENERATE_MIPS ; 
 int /*<<< orphan*/  D3D10_USAGE_DYNAMIC ; 
#define  DXGI_FORMAT_R32G32_FLOAT 131 
 int /*<<< orphan*/  DXGI_FORMAT_R8G8B8A8_UNORM ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_SHADER_HLSL ; 
 int RARCH_SHADER_SLANG ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 unsigned int SLANG_CBUFFER_MAX ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  countof (TYPE_21__ const*) ; 
 int /*<<< orphan*/  d3d10_free_shader_preset (TYPE_19__*) ; 
 int /*<<< orphan*/  d3d10_init_shader (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ *,TYPE_21__ const*,int /*<<< orphan*/ ,TYPE_28__*) ; 
 int /*<<< orphan*/  d3d10_init_texture (int /*<<< orphan*/ ,TYPE_25__*) ; 
 int /*<<< orphan*/  d3d10_update_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_25__*) ; 
#define  d3d10_vertex_t 130 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  image_texture_free (struct texture_image*) ; 
 int /*<<< orphan*/  image_texture_load (struct texture_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
#define  position 129 
 int /*<<< orphan*/  slang_process (struct video_shader*,unsigned int,int /*<<< orphan*/ ,int,TYPE_18__*,TYPE_24__*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
#define  texcoord 128 
 int /*<<< orphan*/  video_shader_read_conf_preset (int /*<<< orphan*/ *,struct video_shader*) ; 
 int /*<<< orphan*/ * video_shader_read_preset (char const*) ; 
 int /*<<< orphan*/  video_shader_resolve_current_parameters (int /*<<< orphan*/ *,struct video_shader*) ; 

__attribute__((used)) static bool d3d10_gfx_set_shader(void* data, enum rarch_shader_type type, const char* path)
{
#if defined(HAVE_SLANG) && defined(HAVE_SPIRV_CROSS)
   unsigned         i;
   config_file_t* conf     = NULL;
   d3d10_texture_t* source = NULL;
   d3d10_video_t*   d3d10  = (d3d10_video_t*)data;

   if (!d3d10)
      return false;

   D3D10Flush(d3d10->device);
   d3d10_free_shader_preset(d3d10);

   if (string_is_empty(path))
      return true;

   if (type != RARCH_SHADER_SLANG)
   {
      RARCH_WARN("[D3D10] Only Slang shaders are supported. Falling back to stock.\n");
      return false;
   }

   if (!(conf = video_shader_read_preset(path)))
      return false;

   d3d10->shader_preset = (struct video_shader*)calloc(1, sizeof(*d3d10->shader_preset));

   if (!video_shader_read_conf_preset(conf, d3d10->shader_preset))
      goto error;

   source = &d3d10->frame.texture[0];
   for (i = 0; i < d3d10->shader_preset->passes; source = &d3d10->pass[i++].rt)
   {
      unsigned j;
      /* clang-format off */
      semantics_map_t semantics_map = {
         {
            /* Original */
            { &d3d10->frame.texture[0].view, 0,
               &d3d10->frame.texture[0].size_data, 0},

            /* Source */
            { &source->view, 0,
               &source->size_data, 0},

            /* OriginalHistory */
            { &d3d10->frame.texture[0].view, sizeof(*d3d10->frame.texture),
               &d3d10->frame.texture[0].size_data, sizeof(*d3d10->frame.texture)},

            /* PassOutput */
            { &d3d10->pass[0].rt.view, sizeof(*d3d10->pass),
               &d3d10->pass[0].rt.size_data, sizeof(*d3d10->pass)},

            /* PassFeedback */
            { &d3d10->pass[0].feedback.view, sizeof(*d3d10->pass),
               &d3d10->pass[0].feedback.size_data, sizeof(*d3d10->pass)},

            /* User */
            { &d3d10->luts[0].view, sizeof(*d3d10->luts),
               &d3d10->luts[0].size_data, sizeof(*d3d10->luts)},
         },
         {
            &d3d10->mvp,                     /* MVP */
            &d3d10->pass[i].rt.size_data,    /* OutputSize */
            &d3d10->frame.output_size,       /* FinalViewportSize */
            &d3d10->pass[i].frame_count,     /* FrameCount */
            &d3d10->pass[i].frame_direction, /* FrameDirection */
         }
      };
      /* clang-format on */

      if (!slang_process(
               d3d10->shader_preset, i, RARCH_SHADER_HLSL, 40, &semantics_map,
               &d3d10->pass[i].semantics))
         goto error;

      {
         static const D3D10_INPUT_ELEMENT_DESC desc[] = {
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(d3d10_vertex_t, position),
               D3D10_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(d3d10_vertex_t, texcoord),
               D3D10_INPUT_PER_VERTEX_DATA, 0 },
         };
#ifdef DEBUG
         bool save_hlsl = true;
#else
         bool save_hlsl = false;
#endif
         static const char vs_ext[] = ".vs.hlsl";
         static const char ps_ext[] = ".ps.hlsl";
         char              vs_path[PATH_MAX_LENGTH] = {0};
         char              ps_path[PATH_MAX_LENGTH] = {0};
         const char*       slang_path = d3d10->shader_preset->pass[i].source.path;
         const char*       vs_src     = d3d10->shader_preset->pass[i].source.string.vertex;
         const char*       ps_src     = d3d10->shader_preset->pass[i].source.string.fragment;

         strlcpy(vs_path, slang_path, sizeof(vs_path));
         strlcpy(ps_path, slang_path, sizeof(ps_path));
         strlcat(vs_path, vs_ext, sizeof(vs_path));
         strlcat(ps_path, ps_ext, sizeof(ps_path));

         if (!d3d10_init_shader(
                  d3d10->device, vs_src, 0, vs_path, "main", NULL, NULL, desc, countof(desc),
                  &d3d10->pass[i].shader))
            save_hlsl = true;

         if (!d3d10_init_shader(
                  d3d10->device, ps_src, 0, ps_path, NULL, "main", NULL, NULL, 0,
                  &d3d10->pass[i].shader))
            save_hlsl = true;

         if (save_hlsl)
         {
            FILE* fp = fopen(vs_path, "w");
            fwrite(vs_src, 1, strlen(vs_src), fp);
            fclose(fp);

            fp = fopen(ps_path, "w");
            fwrite(ps_src, 1, strlen(ps_src), fp);
            fclose(fp);
         }

         free(d3d10->shader_preset->pass[i].source.string.vertex);
         free(d3d10->shader_preset->pass[i].source.string.fragment);

         d3d10->shader_preset->pass[i].source.string.vertex   = NULL;
         d3d10->shader_preset->pass[i].source.string.fragment = NULL;

         if (!d3d10->pass[i].shader.vs || !d3d10->pass[i].shader.ps)
            goto error;
      }

      for (j = 0; j < SLANG_CBUFFER_MAX; j++)
      {
         D3D10_BUFFER_DESC desc;
         desc.ByteWidth           = d3d10->pass[i].semantics.cbuffers[j].size;
         desc.Usage               = D3D10_USAGE_DYNAMIC;
         desc.BindFlags           = D3D10_BIND_CONSTANT_BUFFER;
         desc.CPUAccessFlags      = D3D10_CPU_ACCESS_WRITE;
         desc.MiscFlags           = 0;

         if (!desc.ByteWidth)
            continue;

         D3D10CreateBuffer(d3d10->device, &desc,
               NULL, &d3d10->pass[i].buffers[j]);
      }
   }

   for (i = 0; i < d3d10->shader_preset->luts; i++)
   {
      struct texture_image image = { 0 };
      image.supports_rgba        = true;

      if (!image_texture_load(&image, d3d10->shader_preset->lut[i].path))
         goto error;

      d3d10->luts[i].desc.Width  = image.width;
      d3d10->luts[i].desc.Height = image.height;
      d3d10->luts[i].desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

      if (d3d10->shader_preset->lut[i].mipmap)
         d3d10->luts[i].desc.MiscFlags = D3D10_RESOURCE_MISC_GENERATE_MIPS;

      d3d10_init_texture(d3d10->device, &d3d10->luts[i]);

      d3d10_update_texture(
            d3d10->device,
            image.width, image.height, 0,
            DXGI_FORMAT_R8G8B8A8_UNORM, image.pixels,
            &d3d10->luts[i]);

      image_texture_free(&image);
   }

   video_shader_resolve_current_parameters(conf, d3d10->shader_preset);
   config_file_free(conf);

   d3d10->resize_render_targets = true;
   d3d10->init_history          = true;

   return true;

error:
   d3d10_free_shader_preset(d3d10);
#endif

   return false;
}