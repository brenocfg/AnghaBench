#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int channels; int sampformat; } ;
struct TYPE_7__ {TYPE_1__ format; } ;
typedef  TYPE_2__ SexyAL_device ;

/* Variables and functions */
 int SexyALI_DSound_RawCanWrite (TYPE_2__*) ; 
 int SexyALI_OSS_RawCanWrite (TYPE_2__*) ; 

__attribute__((used)) static uint32_t CanWrite(SexyAL_device *device)
{
 uint32_t bytes,frames;

 #ifdef WIN32
 bytes=SexyALI_DSound_RawCanWrite(device);
 #else
 bytes=SexyALI_OSS_RawCanWrite(device);
 #endif
 frames=bytes / device->format.channels / (device->format.sampformat>>4);

 return(frames);
}