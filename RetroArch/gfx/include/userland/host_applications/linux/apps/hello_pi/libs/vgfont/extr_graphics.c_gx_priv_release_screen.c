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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {scalar_t__* refcounts; int /*<<< orphan*/  lock; int /*<<< orphan*/ * screens; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPMANX_NO_HANDLE ; 
 TYPE_1__ gx ; 
 int /*<<< orphan*/  vc_dispmanx_display_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int32_t gx_priv_release_screen(uint32_t index)
{
   vcos_mutex_lock(&gx.lock);
   gx.refcounts[index]--;
   if (gx.refcounts[index] == 0)
   {
      vc_dispmanx_display_close(gx.screens[index]);
      gx.screens[index] = DISPMANX_NO_HANDLE;
   }
   vcos_mutex_unlock(&gx.lock);
   return 0;
}