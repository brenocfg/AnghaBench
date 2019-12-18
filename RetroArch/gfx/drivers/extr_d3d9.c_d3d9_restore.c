#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int needs_restore; int /*<<< orphan*/  video_info; } ;
typedef  TYPE_1__ d3d9_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  d3d9_deinitialize (TYPE_1__*) ; 
 int /*<<< orphan*/  d3d9_initialize (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool d3d9_restore(void *data)
{
   d3d9_video_t            *d3d = (d3d9_video_t*)data;

   if (!d3d)
      return false;

   d3d9_deinitialize(d3d);

   if (!d3d9_initialize(d3d, &d3d->video_info))
   {
      RARCH_ERR("[D3D9]: Restore error.\n");
      return false;
   }

   d3d->needs_restore = false;

   return true;
}