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
struct TYPE_2__ {size_t buffer_size; } ;
struct audio_info {TYPE_1__ play; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_GETINFO ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct audio_info*) ; 

__attribute__((used)) static size_t audioio_buffer_size(void *data)
{
   struct audio_info info;
   int *fd = (int*)data;

   if (ioctl(*fd, AUDIO_GETINFO, &info) < 0)
      return false;

   return info.play.buffer_size;
}