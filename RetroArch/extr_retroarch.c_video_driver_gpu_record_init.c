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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ malloc (unsigned int) ; 
 int /*<<< orphan*/ * video_driver_record_gpu_buffer ; 

__attribute__((used)) static bool video_driver_gpu_record_init(unsigned size)
{
   video_driver_record_gpu_buffer = (uint8_t*)malloc(size);
   if (!video_driver_record_gpu_buffer)
      return false;
   return true;
}