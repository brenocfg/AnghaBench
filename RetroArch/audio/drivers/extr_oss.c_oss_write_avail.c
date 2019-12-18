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
struct TYPE_3__ {size_t bytes; } ;
typedef  TYPE_1__ audio_buf_info ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  SNDCTL_DSP_GETOSPACE ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static size_t oss_write_avail(void *data)
{
   audio_buf_info info;
   int *fd = (int*)data;

   if (ioctl(*fd, SNDCTL_DSP_GETOSPACE, &info) < 0)
   {
      RARCH_ERR("[OSS]: SNDCTL_DSP_GETOSPACE failed ...\n");
      return 0;
   }

   return info.bytes;
}