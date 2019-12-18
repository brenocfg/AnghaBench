#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  features; } ;
typedef  int EGLenum ;

/* Variables and functions */
 int EGL_MAX_CONFIGS ; 
#define  EGL_NO_TEXTURE 130 
#define  EGL_TEXTURE_RGB 129 
#define  EGL_TEXTURE_RGBA 128 
 int /*<<< orphan*/  UNREACHABLE () ; 
 int bindable_rgb (int /*<<< orphan*/ ) ; 
 int bindable_rgba (int /*<<< orphan*/ ) ; 
 TYPE_1__* formats ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

bool egl_config_bindable(int id, EGLenum format)
{
   vcos_assert(id >= 0 && id < EGL_MAX_CONFIGS);
   switch (format) {
   case EGL_NO_TEXTURE:
      return true;
   case EGL_TEXTURE_RGB:
      return bindable_rgb(formats[id].features);
   case EGL_TEXTURE_RGBA:
      return bindable_rgba(formats[id].features);
   default:
      UNREACHABLE();
      return false;
   }
}