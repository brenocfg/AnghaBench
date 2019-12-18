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
struct TYPE_2__ {int /*<<< orphan*/  tex_filter; } ;
typedef  TYPE_1__ psp1_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  GU_LINEAR ; 
 int /*<<< orphan*/  GU_NEAREST ; 

__attribute__((used)) static void psp_set_filtering(void *data, unsigned index, bool smooth)
{
   psp1_video_t *psp = (psp1_video_t*)data;

   if (psp)
      psp->tex_filter = smooth? GU_LINEAR : GU_NEAREST;
}