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
typedef  int /*<<< orphan*/  hlsl_renderchain_t ;
typedef  int /*<<< orphan*/  d3d9_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 

__attribute__((used)) static bool hlsl_d3d9_renderchain_init_shader(d3d9_video_t *d3d,
      hlsl_renderchain_t *chain)
{
   RARCH_LOG("[D3D9]: Using HLSL shader backend.\n");

   return true;
}