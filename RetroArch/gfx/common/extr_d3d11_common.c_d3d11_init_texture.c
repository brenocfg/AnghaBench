#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int Count; scalar_t__ Quality; } ;
struct TYPE_15__ {int BindFlags; int MipLevels; int ArraySize; scalar_t__ Usage; int MiscFlags; int Width; int Height; void* CPUAccessFlags; int /*<<< orphan*/  Format; TYPE_1__ SampleDesc; } ;
struct TYPE_13__ {int x; int y; float z; float w; } ;
struct TYPE_14__ {TYPE_5__ desc; TYPE_3__ size_data; int /*<<< orphan*/  staging; int /*<<< orphan*/  rt_view; int /*<<< orphan*/  handle; int /*<<< orphan*/  view; } ;
typedef  TYPE_4__ d3d11_texture_t ;
typedef  int UINT ;
struct TYPE_12__ {int MipLevels; scalar_t__ MostDetailedMip; } ;
struct TYPE_16__ {TYPE_2__ Texture2D; int /*<<< orphan*/  ViewDimension; int /*<<< orphan*/  Format; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ D3D11_TEXTURE2D_DESC ;
typedef  TYPE_6__ D3D11_SHADER_RESOURCE_VIEW_DESC ;
typedef  int /*<<< orphan*/  D3D11Device ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11CreateTexture2D (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D11CreateTexture2DRenderTargetView (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  D3D11CreateTexture2DShaderResourceView (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int D3D11_BIND_RENDER_TARGET ; 
 int D3D11_BIND_SHADER_RESOURCE ; 
 void* D3D11_CPU_ACCESS_WRITE ; 
 int D3D11_FORMAT_SUPPORT_RENDER_TARGET ; 
 int D3D11_FORMAT_SUPPORT_SHADER_SAMPLE ; 
 int D3D11_FORMAT_SUPPORT_TEXTURE2D ; 
 int D3D11_RESOURCE_MISC_GENERATE_MIPS ; 
 scalar_t__ D3D11_USAGE_DYNAMIC ; 
 scalar_t__ D3D11_USAGE_STAGING ; 
 int /*<<< orphan*/  D3D_SRV_DIMENSION_TEXTURE2D ; 
 int /*<<< orphan*/  DXGI_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  d3d11_get_closest_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d3d11_release_texture (TYPE_4__*) ; 

void d3d11_init_texture(D3D11Device device, d3d11_texture_t* texture)
{
   bool is_render_target = texture->desc.BindFlags & D3D11_BIND_RENDER_TARGET;
   UINT format_support   = D3D11_FORMAT_SUPPORT_TEXTURE2D | D3D11_FORMAT_SUPPORT_SHADER_SAMPLE;

   d3d11_release_texture(texture);

   texture->desc.MipLevels          = 1;
   texture->desc.ArraySize          = 1;
   texture->desc.SampleDesc.Count   = 1;
   texture->desc.SampleDesc.Quality = 0;
   texture->desc.BindFlags         |= D3D11_BIND_SHADER_RESOURCE;
   texture->desc.CPUAccessFlags     =
      texture->desc.Usage == D3D11_USAGE_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;

   if (texture->desc.MiscFlags & D3D11_RESOURCE_MISC_GENERATE_MIPS)
   {
      unsigned width, height;

      texture->desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
      width                    = texture->desc.Width >> 5;
      height                   = texture->desc.Height >> 5;

      while (width && height)
      {
         width >>= 1;
         height >>= 1;
         texture->desc.MipLevels++;
      }
   }

   if (texture->desc.BindFlags & D3D11_BIND_RENDER_TARGET)
      format_support |= D3D11_FORMAT_SUPPORT_RENDER_TARGET;

   texture->desc.Format = d3d11_get_closest_match(device, texture->desc.Format, format_support);

   D3D11CreateTexture2D(device, &texture->desc, NULL, &texture->handle);

   {
      D3D11_SHADER_RESOURCE_VIEW_DESC view_desc = { DXGI_FORMAT_UNKNOWN };
      view_desc.Format                          = texture->desc.Format;
      view_desc.ViewDimension                   = D3D_SRV_DIMENSION_TEXTURE2D;
      view_desc.Texture2D.MostDetailedMip       = 0;
      view_desc.Texture2D.MipLevels             = -1;
      D3D11CreateTexture2DShaderResourceView(device, texture->handle, &view_desc, &texture->view);
   }

   if (is_render_target)
      D3D11CreateTexture2DRenderTargetView(device, texture->handle, NULL, &texture->rt_view);
   else
   {
      D3D11_TEXTURE2D_DESC desc = texture->desc;
      desc.MipLevels            = 1;
      desc.BindFlags            = 0;
      desc.MiscFlags            = 0;
      desc.Usage                = D3D11_USAGE_STAGING;
      desc.CPUAccessFlags       = D3D11_CPU_ACCESS_WRITE;
      D3D11CreateTexture2D(device, &desc, NULL, &texture->staging);
   }

   texture->size_data.x = texture->desc.Width;
   texture->size_data.y = texture->desc.Height;
   texture->size_data.z = 1.0f / texture->desc.Width;
   texture->size_data.w = 1.0f / texture->desc.Height;
}