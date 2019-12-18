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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int EGL_OPENVG_BIT ; 
 scalar_t__ FEATURES_UNPACK_MULTI (int /*<<< orphan*/ ) ; 
 int egl_config_get_api_support (int) ; 
 TYPE_1__* formats ; 

uint32_t egl_config_get_api_conformance(int id)
{
   /* vg doesn't support multisampled surfaces properly */
   return egl_config_get_api_support(id) & ~(FEATURES_UNPACK_MULTI(formats[id].features) ? EGL_OPENVG_BIT : 0);
}