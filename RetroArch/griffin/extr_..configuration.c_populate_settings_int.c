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
struct config_int_setting {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  content_favorites_size; int /*<<< orphan*/  d3d12_gpu_index; int /*<<< orphan*/  d3d11_gpu_index; int /*<<< orphan*/  d3d10_gpu_index; int /*<<< orphan*/  vulkan_gpu_index; int /*<<< orphan*/  crt_switch_center_adjust; int /*<<< orphan*/  audio_wasapi_sh_buffer_length; int /*<<< orphan*/  netplay_check_frames; int /*<<< orphan*/  state_slot; } ;
struct TYPE_5__ {TYPE_1__ ints; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CRT_SWITCH_CENTER_ADJUST ; 
 int /*<<< orphan*/  DEFAULT_D3D10_GPU_INDEX ; 
 int /*<<< orphan*/  DEFAULT_D3D11_GPU_INDEX ; 
 int /*<<< orphan*/  DEFAULT_D3D12_GPU_INDEX ; 
 int /*<<< orphan*/  DEFAULT_VULKAN_GPU_INDEX ; 
 int /*<<< orphan*/  RARCH_OVERRIDE_SETTING_NETPLAY_CHECK_FRAMES ; 
 int /*<<< orphan*/  SETTING_INT (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SETTING_OVERRIDE (int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  default_content_favorites_size ; 
 int /*<<< orphan*/  netplay_check_frames ; 
 int /*<<< orphan*/  wasapi_sh_buffer_length ; 

__attribute__((used)) static struct config_int_setting *populate_settings_int(settings_t *settings, int *size)
{
   unsigned count                     = 0;
   struct config_int_setting  *tmp    = (struct config_int_setting*)calloc((*size + 1), sizeof(struct config_int_setting));

   if (!tmp)
      return NULL;

   SETTING_INT("state_slot",                   &settings->ints.state_slot, false, 0 /* TODO */, false);
#ifdef HAVE_NETWORKING
   SETTING_INT("netplay_check_frames",         &settings->ints.netplay_check_frames, true, netplay_check_frames, false);
   SETTING_OVERRIDE(RARCH_OVERRIDE_SETTING_NETPLAY_CHECK_FRAMES);
#endif
#ifdef HAVE_WASAPI
   SETTING_INT("audio_wasapi_sh_buffer_length", &settings->ints.audio_wasapi_sh_buffer_length, true, wasapi_sh_buffer_length, false);
#endif
   SETTING_INT("crt_switch_center_adjust",      &settings->ints.crt_switch_center_adjust, false, DEFAULT_CRT_SWITCH_CENTER_ADJUST, false);
#ifdef HAVE_VULKAN
   SETTING_INT("vulkan_gpu_index",              &settings->ints.vulkan_gpu_index, true, DEFAULT_VULKAN_GPU_INDEX, false);
#endif
#ifdef HAVE_D3D10
   SETTING_INT("d3d10_gpu_index",              &settings->ints.d3d10_gpu_index, true, DEFAULT_D3D10_GPU_INDEX, false);
#endif
#ifdef HAVE_D3D11
   SETTING_INT("d3d11_gpu_index",              &settings->ints.d3d11_gpu_index, true, DEFAULT_D3D11_GPU_INDEX, false);
#endif
#ifdef HAVE_D3D12
   SETTING_INT("d3d12_gpu_index",              &settings->ints.d3d12_gpu_index, true, DEFAULT_D3D12_GPU_INDEX, false);
#endif
   SETTING_INT("content_favorites_size",       &settings->ints.content_favorites_size, true, default_content_favorites_size, false);

   *size = count;

   return tmp;
}