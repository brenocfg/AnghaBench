#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {scalar_t__ private; } ;
typedef  TYPE_1__ SexyAL_device ;

/* Variables and functions */
 scalar_t__ write (int,void*,scalar_t__) ; 

uint32_t SexyALI_OSS_RawWrite(SexyAL_device *device, void *data, uint32_t len)
{
 ssize_t bytes;

 bytes = write(*(int *)device->private,data,len);
 if(bytes <= 0) return(0);			/* FIXME:  What to do on -1? */
 return(bytes);
}