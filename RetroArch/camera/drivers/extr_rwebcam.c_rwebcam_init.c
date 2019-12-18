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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 void* RWebCamInit (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void *rwebcam_init(const char *device, uint64_t caps,
      unsigned width, unsigned height)
{
   (void)device;
   return RWebCamInit(caps, width, height);
}