#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  format; int /*<<< orphan*/  srcformat; } ;
typedef  TYPE_1__ SexyAL_device ;

/* Variables and functions */
 int /*<<< orphan*/  FtoB (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SexiALI_Convert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  SexyALI_DSound_RawWrite (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SexyALI_OSS_RawWrite (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t Write(SexyAL_device *device, void *data, uint32_t frames)
{
 uint8_t buffer[2048*4];

 while(frames)
 {
  int32_t tmp;

  tmp=frames;
  if(tmp>2048) 
  { 
   tmp=2048;
   frames-=2048;
  }
  else frames-=tmp;

  SexiALI_Convert(&device->srcformat, &device->format, buffer, data, tmp);
  //printf("%02x, %02x, %02x\n", device->srcformat.sampformat, device->srcformat.byteorder, device->srcformat.channels);
  //printf("buffer: %d\n",buffer[0]);
  /* FIXME:  Return the actual number of frame written. It should always equal
             the number of frames requested to be written, except in cases of sound device
	     failures.  
  */
  #ifdef WIN32
  SexyALI_DSound_RawWrite(device,buffer,FtoB(&device->format,tmp));
  #else
  SexyALI_OSS_RawWrite(device,buffer,FtoB(&device->format,tmp));
  #endif
 }
 return(frames);
}