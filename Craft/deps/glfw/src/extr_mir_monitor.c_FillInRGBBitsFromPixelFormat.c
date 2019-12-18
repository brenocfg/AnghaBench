#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int redBits; int greenBits; int blueBits; } ;
typedef  int MirPixelFormat ;
typedef  TYPE_1__ GLFWvidmode ;

/* Variables and functions */
#define  mir_pixel_format_abgr_8888 136 
#define  mir_pixel_format_argb_8888 135 
#define  mir_pixel_format_bgr_888 134 
#define  mir_pixel_format_rgb_565 133 
#define  mir_pixel_format_rgb_888 132 
#define  mir_pixel_format_rgba_4444 131 
#define  mir_pixel_format_rgba_5551 130 
#define  mir_pixel_format_xbgr_8888 129 
#define  mir_pixel_format_xrgb_8888 128 

void FillInRGBBitsFromPixelFormat(GLFWvidmode* mode, const MirPixelFormat pf)
{
    switch (pf)
    {
      case mir_pixel_format_rgb_565:
          mode->redBits   = 5;
          mode->greenBits = 6;
          mode->blueBits  = 5;
          break;
      case mir_pixel_format_rgba_5551:
          mode->redBits   = 5;
          mode->greenBits = 5;
          mode->blueBits  = 5;
          break;
      case mir_pixel_format_rgba_4444:
          mode->redBits   = 4;
          mode->greenBits = 4;
          mode->blueBits  = 4;
          break;
      case mir_pixel_format_abgr_8888:
      case mir_pixel_format_xbgr_8888:
      case mir_pixel_format_argb_8888:
      case mir_pixel_format_xrgb_8888:
      case mir_pixel_format_bgr_888:
      case mir_pixel_format_rgb_888:
      default:
          mode->redBits   = 8;
          mode->greenBits = 8;
          mode->blueBits  = 8;
          break;
    }
}