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
struct cdrom_device_info {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* audio_ioctl ) (struct cdrom_device_info*,unsigned int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_PLAY_AUDIO ; 
 int /*<<< orphan*/  CDROM_CAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CD_DO_IOCTL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  cdinfo (int /*<<< orphan*/ ,char*) ; 
 int check_for_audio_disc (struct cdrom_device_info*,TYPE_1__*) ; 
 int stub1 (struct cdrom_device_info*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdrom_ioctl_audioctl(struct cdrom_device_info *cdi,
		unsigned int cmd)
{
	int ret;

	cdinfo(CD_DO_IOCTL, "doing audio ioctl (start/stop/pause/resume)\n");

	if (!CDROM_CAN(CDC_PLAY_AUDIO))
		return -ENOSYS;
	ret = check_for_audio_disc(cdi, cdi->ops);
	if (ret)
		return ret;
	return cdi->ops->audio_ioctl(cdi, cmd, NULL);
}