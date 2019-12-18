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
typedef  int /*<<< orphan*/  xmb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_driver_monitor_reset () ; 
 int /*<<< orphan*/  xmb_context_reset_internal (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void xmb_context_reset(void *data, bool is_threaded)
{
   xmb_handle_t *xmb = (xmb_handle_t*)data;

   if (xmb)
      xmb_context_reset_internal(xmb, is_threaded, true);
   video_driver_monitor_reset();
}