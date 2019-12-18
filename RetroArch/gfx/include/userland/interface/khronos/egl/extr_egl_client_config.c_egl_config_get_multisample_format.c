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
struct TYPE_2__ {int /*<<< orphan*/  multisample; } ;
typedef  int /*<<< orphan*/  KHRN_IMAGE_FORMAT_T ;

/* Variables and functions */
 int EGL_MAX_CONFIGS ; 
 TYPE_1__* formats ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

KHRN_IMAGE_FORMAT_T egl_config_get_multisample_format(int id)
{
   vcos_assert(id >= 0 && id < EGL_MAX_CONFIGS);

   return formats[id].multisample;
}