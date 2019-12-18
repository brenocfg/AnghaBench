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
 int glsl_core ; 
 unsigned int glsl_major ; 
 unsigned int glsl_minor ; 

void gl_glsl_set_context_type(bool core_profile,
      unsigned major, unsigned minor)
{
   glsl_core = core_profile;
   glsl_major = major;
   glsl_minor = minor;
}