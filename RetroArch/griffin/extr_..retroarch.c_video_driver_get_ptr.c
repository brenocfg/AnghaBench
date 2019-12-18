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
 void* video_driver_get_ptr_internal (int) ; 

void *video_driver_get_ptr(bool force_nonthreaded_data)
{
   return video_driver_get_ptr_internal(force_nonthreaded_data);
}