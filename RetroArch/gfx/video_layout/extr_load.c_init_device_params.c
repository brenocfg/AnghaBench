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
typedef  int /*<<< orphan*/  scope_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scope_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * video_layout_internal_device_params ; 

__attribute__((used)) static void init_device_params(scope_t *scope)
{
   size_t i;

   for (i = 0; i < ARRAY_SIZE(video_layout_internal_device_params); i += 2)
   {
      scope_param(scope, video_layout_internal_device_params[i], video_layout_internal_device_params[i + 1]);
   }
}