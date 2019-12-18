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
 int /*<<< orphan*/  raspicamcontrol_get_camera (int*,int*) ; 
 int raspicamcontrol_get_mem_gpu () ; 
 int /*<<< orphan*/  vcos_log_error (char*,...) ; 

void raspicamcontrol_check_configuration(int min_gpu_mem)
{
   int gpu_mem = raspicamcontrol_get_mem_gpu();
   int supported = 0, detected = 0;
   raspicamcontrol_get_camera(&supported, &detected);
   if (!supported)
      vcos_log_error("Camera is not enabled in this build. Try running \"sudo raspi-config\" and ensure that \"camera\" has been enabled\n");
   else if (gpu_mem < min_gpu_mem)
      vcos_log_error("Only %dM of gpu_mem is configured. Try running \"sudo raspi-config\" and ensure that \"memory_split\" has a value of %d or greater\n", gpu_mem, min_gpu_mem);
   else if (!detected)
      vcos_log_error("Camera is not detected. Please check carefully the camera module is installed correctly\n");
   else
      vcos_log_error("Failed to run camera app. Please check for firmware updates\n");
}