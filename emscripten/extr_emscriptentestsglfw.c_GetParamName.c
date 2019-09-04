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
#define  GLFW_ACCELERATED 168 
#define  GLFW_ACCUM_ALPHA_BITS 167 
#define  GLFW_ACCUM_BLUE_BITS 166 
#define  GLFW_ACCUM_GREEN_BITS 165 
#define  GLFW_ACCUM_RED_BITS 164 
#define  GLFW_ACTIVE 163 
#define  GLFW_ALPHA_BITS 162 
#define  GLFW_ALPHA_MAP_BIT 161 
#define  GLFW_AUTO_POLL_EVENTS 160 
#define  GLFW_AUX_BUFFERS 159 
#define  GLFW_BLUE_BITS 158 
#define  GLFW_BUILD_MIPMAPS_BIT 157 
#define  GLFW_BUTTONS 156 
#define  GLFW_DEPTH_BITS 155 
#define  GLFW_FSAA_SAMPLES 154 
#define  GLFW_FULLSCREEN 153 
#define  GLFW_GREEN_BITS 152 
#define  GLFW_ICONIFIED 151 
#define  GLFW_KEY_REPEAT 150 
#define  GLFW_MOUSE_CURSOR 149 
#define  GLFW_NOWAIT 148 
#define  GLFW_NO_RESCALE_BIT 147 
#define  GLFW_OPENED 146 
#define  GLFW_OPENGL_COMPAT_PROFILE 145 
#define  GLFW_OPENGL_CORE_PROFILE 144 
#define  GLFW_OPENGL_DEBUG_CONTEXT 143 
#define  GLFW_OPENGL_FORWARD_COMPAT 142 
#define  GLFW_OPENGL_PROFILE 141 
#define  GLFW_OPENGL_VERSION_MAJOR 140 
#define  GLFW_OPENGL_VERSION_MINOR 139 
#define  GLFW_ORIGIN_UL_BIT 138 
#define  GLFW_RED_BITS 137 
#define  GLFW_REFRESH_RATE 136 
#define  GLFW_STENCIL_BITS 135 
#define  GLFW_STEREO 134 
#define  GLFW_STICKY_KEYS 133 
#define  GLFW_STICKY_MOUSE_BUTTONS 132 
#define  GLFW_SYSTEM_KEYS 131 
#define  GLFW_WAIT 130 
#define  GLFW_WINDOW 129 
#define  GLFW_WINDOW_NO_RESIZE 128 

char* GetParamName(int param){
  switch(param){
    case GLFW_WINDOW               : return "GLFW_WINDOW";
    case GLFW_FULLSCREEN           : return "GLFW_FULLSCREEN";
    case GLFW_OPENED               : return "GLFW_OPENED";
    case GLFW_ACTIVE               : return "GLFW_ACTIVE";
    case GLFW_ICONIFIED            : return "GLFW_ICONIFIED";
    case GLFW_ACCELERATED          : return "GLFW_ACCELERATED";
    case GLFW_RED_BITS             : return "GLFW_RED_BITS";
    case GLFW_GREEN_BITS           : return "GLFW_GREEN_BITS";
    case GLFW_BLUE_BITS            : return "GLFW_BLUE_BITS";
    case GLFW_ALPHA_BITS           : return "GLFW_ALPHA_BITS";
    case GLFW_DEPTH_BITS           : return "GLFW_DEPTH_BITS";
    case GLFW_STENCIL_BITS         : return "GLFW_STENCIL_BITS";
    case GLFW_REFRESH_RATE         : return "GLFW_REFRESH_RATE";
    case GLFW_ACCUM_RED_BITS       : return "GLFW_ACCUM_RED_BITS";
    case GLFW_ACCUM_GREEN_BITS     : return "GLFW_ACCUM_GREEN_BITS";
    case GLFW_ACCUM_BLUE_BITS      : return "GLFW_BLUE_BITS";
    case GLFW_ACCUM_ALPHA_BITS     : return "GLFW_ALPHA_BITS";
    case GLFW_AUX_BUFFERS          : return "GLFW_AUX_BUFFERS";
    case GLFW_STEREO               : return "GLFW_STEREO";
    case GLFW_WINDOW_NO_RESIZE     : return "GLFW_WINDOW_NO_RESIZE";
    case GLFW_FSAA_SAMPLES         : return "GLFW_FSAA_SAMPLES";
    case GLFW_OPENGL_VERSION_MAJOR : return "GLFW_OPENGL_VERSION_MAJOR";
    case GLFW_OPENGL_VERSION_MINOR : return "GLFW_OPENGL_VERSION_MINOR";
    case GLFW_OPENGL_FORWARD_COMPAT : return "GLFW_OPENGL_FORWARD_COMPAT";
    case GLFW_OPENGL_DEBUG_CONTEXT : return "GLFW_OPENGL_DEBUG_CONTEXT";
    case GLFW_OPENGL_PROFILE       : return "GLFW_OPENGL_PROFILE";
    case GLFW_OPENGL_CORE_PROFILE  : return "GLFW_OPENGL_CORE_PROFILE | GLFW_PRESENT";
    case GLFW_OPENGL_COMPAT_PROFILE : return "GLFW_OPENGL_COMPAT_PROFILE | GLFW_AXES";
    case GLFW_MOUSE_CURSOR         : return "GLFW_MOUSE_CURSOR";
    case GLFW_STICKY_KEYS          : return "GLFW_STICKY_KEYS";
    case GLFW_STICKY_MOUSE_BUTTONS : return "GLFW_STICKY_MOUSE_BUTTONS";
    case GLFW_SYSTEM_KEYS          : return "GLFW_SYSTEM_KEYS";
    case GLFW_KEY_REPEAT           : return "GLFW_KEY_REPEAT";
    case GLFW_AUTO_POLL_EVENTS     : return "GLFW_AUTO_POLL_EVENTS";
    case GLFW_WAIT                 : return "GLFW_WAIT";
    case GLFW_NOWAIT               : return "GLFW_NOWAIT";
    case GLFW_BUTTONS              : return "GLFW_BUTTONS";
    case GLFW_NO_RESCALE_BIT       : return "GLFW_NO_RESCALE_BIT";
    case GLFW_ORIGIN_UL_BIT        : return "GLFW_ORIGIN_UL_BIT";
    case GLFW_BUILD_MIPMAPS_BIT    : return "GLFW_BUILD_MIPMAPS_BIT";
    case GLFW_ALPHA_MAP_BIT        : return "GLFW_ALPHA_MAP_BIT";
    default                        : return "Invalid param";
  }
}