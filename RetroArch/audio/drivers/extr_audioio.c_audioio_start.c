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
struct TYPE_2__ {int pause; } ;
struct audio_info {TYPE_1__ play; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_FLUSH ; 
 int /*<<< orphan*/  AUDIO_GETINFO ; 
 int /*<<< orphan*/  AUDIO_SETINFO ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct audio_info*) ; 

__attribute__((used)) static bool audioio_start(void *data, bool is_shutdown)
{
   struct audio_info info;
   int *fd = (int*)data;

#ifdef AUDIO_FLUSH
   if (ioctl(*fd, AUDIO_FLUSH, NULL) < 0)
      return false;
#endif

   if (ioctl(*fd, AUDIO_GETINFO, &info) < 0)
      return false;

   info.play.pause = false;

   return ioctl(*fd, AUDIO_SETINFO, &info) == 0;
}