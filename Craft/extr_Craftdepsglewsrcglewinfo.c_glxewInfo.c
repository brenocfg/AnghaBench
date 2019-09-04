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

/* Variables and functions */

__attribute__((used)) static void glxewInfo ()
{
#ifdef GLX_VERSION_1_2
  _glewInfo_GLX_VERSION_1_2();
#endif /* GLX_VERSION_1_2 */
#ifdef GLX_VERSION_1_3
  _glewInfo_GLX_VERSION_1_3();
#endif /* GLX_VERSION_1_3 */
#ifdef GLX_VERSION_1_4
  _glewInfo_GLX_VERSION_1_4();
#endif /* GLX_VERSION_1_4 */
#ifdef GLX_3DFX_multisample
  _glewInfo_GLX_3DFX_multisample();
#endif /* GLX_3DFX_multisample */
#ifdef GLX_AMD_gpu_association
  _glewInfo_GLX_AMD_gpu_association();
#endif /* GLX_AMD_gpu_association */
#ifdef GLX_ARB_create_context
  _glewInfo_GLX_ARB_create_context();
#endif /* GLX_ARB_create_context */
#ifdef GLX_ARB_create_context_profile
  _glewInfo_GLX_ARB_create_context_profile();
#endif /* GLX_ARB_create_context_profile */
#ifdef GLX_ARB_create_context_robustness
  _glewInfo_GLX_ARB_create_context_robustness();
#endif /* GLX_ARB_create_context_robustness */
#ifdef GLX_ARB_fbconfig_float
  _glewInfo_GLX_ARB_fbconfig_float();
#endif /* GLX_ARB_fbconfig_float */
#ifdef GLX_ARB_framebuffer_sRGB
  _glewInfo_GLX_ARB_framebuffer_sRGB();
#endif /* GLX_ARB_framebuffer_sRGB */
#ifdef GLX_ARB_get_proc_address
  _glewInfo_GLX_ARB_get_proc_address();
#endif /* GLX_ARB_get_proc_address */
#ifdef GLX_ARB_multisample
  _glewInfo_GLX_ARB_multisample();
#endif /* GLX_ARB_multisample */
#ifdef GLX_ARB_robustness_application_isolation
  _glewInfo_GLX_ARB_robustness_application_isolation();
#endif /* GLX_ARB_robustness_application_isolation */
#ifdef GLX_ARB_robustness_share_group_isolation
  _glewInfo_GLX_ARB_robustness_share_group_isolation();
#endif /* GLX_ARB_robustness_share_group_isolation */
#ifdef GLX_ARB_vertex_buffer_object
  _glewInfo_GLX_ARB_vertex_buffer_object();
#endif /* GLX_ARB_vertex_buffer_object */
#ifdef GLX_ATI_pixel_format_float
  _glewInfo_GLX_ATI_pixel_format_float();
#endif /* GLX_ATI_pixel_format_float */
#ifdef GLX_ATI_render_texture
  _glewInfo_GLX_ATI_render_texture();
#endif /* GLX_ATI_render_texture */
#ifdef GLX_EXT_create_context_es2_profile
  _glewInfo_GLX_EXT_create_context_es2_profile();
#endif /* GLX_EXT_create_context_es2_profile */
#ifdef GLX_EXT_create_context_es_profile
  _glewInfo_GLX_EXT_create_context_es_profile();
#endif /* GLX_EXT_create_context_es_profile */
#ifdef GLX_EXT_fbconfig_packed_float
  _glewInfo_GLX_EXT_fbconfig_packed_float();
#endif /* GLX_EXT_fbconfig_packed_float */
#ifdef GLX_EXT_framebuffer_sRGB
  _glewInfo_GLX_EXT_framebuffer_sRGB();
#endif /* GLX_EXT_framebuffer_sRGB */
#ifdef GLX_EXT_import_context
  _glewInfo_GLX_EXT_import_context();
#endif /* GLX_EXT_import_context */
#ifdef GLX_EXT_scene_marker
  _glewInfo_GLX_EXT_scene_marker();
#endif /* GLX_EXT_scene_marker */
#ifdef GLX_EXT_swap_control
  _glewInfo_GLX_EXT_swap_control();
#endif /* GLX_EXT_swap_control */
#ifdef GLX_EXT_swap_control_tear
  _glewInfo_GLX_EXT_swap_control_tear();
#endif /* GLX_EXT_swap_control_tear */
#ifdef GLX_EXT_texture_from_pixmap
  _glewInfo_GLX_EXT_texture_from_pixmap();
#endif /* GLX_EXT_texture_from_pixmap */
#ifdef GLX_EXT_visual_info
  _glewInfo_GLX_EXT_visual_info();
#endif /* GLX_EXT_visual_info */
#ifdef GLX_EXT_visual_rating
  _glewInfo_GLX_EXT_visual_rating();
#endif /* GLX_EXT_visual_rating */
#ifdef GLX_INTEL_swap_event
  _glewInfo_GLX_INTEL_swap_event();
#endif /* GLX_INTEL_swap_event */
#ifdef GLX_MESA_agp_offset
  _glewInfo_GLX_MESA_agp_offset();
#endif /* GLX_MESA_agp_offset */
#ifdef GLX_MESA_copy_sub_buffer
  _glewInfo_GLX_MESA_copy_sub_buffer();
#endif /* GLX_MESA_copy_sub_buffer */
#ifdef GLX_MESA_pixmap_colormap
  _glewInfo_GLX_MESA_pixmap_colormap();
#endif /* GLX_MESA_pixmap_colormap */
#ifdef GLX_MESA_release_buffers
  _glewInfo_GLX_MESA_release_buffers();
#endif /* GLX_MESA_release_buffers */
#ifdef GLX_MESA_set_3dfx_mode
  _glewInfo_GLX_MESA_set_3dfx_mode();
#endif /* GLX_MESA_set_3dfx_mode */
#ifdef GLX_MESA_swap_control
  _glewInfo_GLX_MESA_swap_control();
#endif /* GLX_MESA_swap_control */
#ifdef GLX_NV_copy_image
  _glewInfo_GLX_NV_copy_image();
#endif /* GLX_NV_copy_image */
#ifdef GLX_NV_float_buffer
  _glewInfo_GLX_NV_float_buffer();
#endif /* GLX_NV_float_buffer */
#ifdef GLX_NV_multisample_coverage
  _glewInfo_GLX_NV_multisample_coverage();
#endif /* GLX_NV_multisample_coverage */
#ifdef GLX_NV_present_video
  _glewInfo_GLX_NV_present_video();
#endif /* GLX_NV_present_video */
#ifdef GLX_NV_swap_group
  _glewInfo_GLX_NV_swap_group();
#endif /* GLX_NV_swap_group */
#ifdef GLX_NV_vertex_array_range
  _glewInfo_GLX_NV_vertex_array_range();
#endif /* GLX_NV_vertex_array_range */
#ifdef GLX_NV_video_capture
  _glewInfo_GLX_NV_video_capture();
#endif /* GLX_NV_video_capture */
#ifdef GLX_NV_video_out
  _glewInfo_GLX_NV_video_out();
#endif /* GLX_NV_video_out */
#ifdef GLX_OML_swap_method
  _glewInfo_GLX_OML_swap_method();
#endif /* GLX_OML_swap_method */
#ifdef GLX_OML_sync_control
  _glewInfo_GLX_OML_sync_control();
#endif /* GLX_OML_sync_control */
#ifdef GLX_SGIS_blended_overlay
  _glewInfo_GLX_SGIS_blended_overlay();
#endif /* GLX_SGIS_blended_overlay */
#ifdef GLX_SGIS_color_range
  _glewInfo_GLX_SGIS_color_range();
#endif /* GLX_SGIS_color_range */
#ifdef GLX_SGIS_multisample
  _glewInfo_GLX_SGIS_multisample();
#endif /* GLX_SGIS_multisample */
#ifdef GLX_SGIS_shared_multisample
  _glewInfo_GLX_SGIS_shared_multisample();
#endif /* GLX_SGIS_shared_multisample */
#ifdef GLX_SGIX_fbconfig
  _glewInfo_GLX_SGIX_fbconfig();
#endif /* GLX_SGIX_fbconfig */
#ifdef GLX_SGIX_hyperpipe
  _glewInfo_GLX_SGIX_hyperpipe();
#endif /* GLX_SGIX_hyperpipe */
#ifdef GLX_SGIX_pbuffer
  _glewInfo_GLX_SGIX_pbuffer();
#endif /* GLX_SGIX_pbuffer */
#ifdef GLX_SGIX_swap_barrier
  _glewInfo_GLX_SGIX_swap_barrier();
#endif /* GLX_SGIX_swap_barrier */
#ifdef GLX_SGIX_swap_group
  _glewInfo_GLX_SGIX_swap_group();
#endif /* GLX_SGIX_swap_group */
#ifdef GLX_SGIX_video_resize
  _glewInfo_GLX_SGIX_video_resize();
#endif /* GLX_SGIX_video_resize */
#ifdef GLX_SGIX_visual_select_group
  _glewInfo_GLX_SGIX_visual_select_group();
#endif /* GLX_SGIX_visual_select_group */
#ifdef GLX_SGI_cushion
  _glewInfo_GLX_SGI_cushion();
#endif /* GLX_SGI_cushion */
#ifdef GLX_SGI_make_current_read
  _glewInfo_GLX_SGI_make_current_read();
#endif /* GLX_SGI_make_current_read */
#ifdef GLX_SGI_swap_control
  _glewInfo_GLX_SGI_swap_control();
#endif /* GLX_SGI_swap_control */
#ifdef GLX_SGI_video_sync
  _glewInfo_GLX_SGI_video_sync();
#endif /* GLX_SGI_video_sync */
#ifdef GLX_SUN_get_transparent_index
  _glewInfo_GLX_SUN_get_transparent_index();
#endif /* GLX_SUN_get_transparent_index */
#ifdef GLX_SUN_video_resize
  _glewInfo_GLX_SUN_video_resize();
#endif /* GLX_SUN_video_resize */
}