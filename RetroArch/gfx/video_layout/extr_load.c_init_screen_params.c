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
 int /*<<< orphan*/  scope_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * video_layout_internal_screen_params ; 

__attribute__((used)) static void init_screen_params(scope_t *scope, int screen_index)
{
   char buf[64];
   size_t i;

   for (i = 0; i < ARRAY_SIZE(video_layout_internal_screen_params); i += 2)
   {
      strcpy(buf, video_layout_internal_screen_params[i + 1]);
      buf[3] = '0' + screen_index;

      scope_param(scope, video_layout_internal_screen_params[i], buf);
   }
}