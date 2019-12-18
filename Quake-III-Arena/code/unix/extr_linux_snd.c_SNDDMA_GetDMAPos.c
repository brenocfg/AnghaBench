#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct count_info {int ptr; } ;
struct TYPE_4__ {int samplebits; } ;
struct TYPE_3__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  SNDCTL_DSP_GETOPTR ; 
 int /*<<< orphan*/  audio_fd ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 TYPE_2__ dma ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct count_info*) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_inited ; 
 TYPE_1__* snddevice ; 

int SNDDMA_GetDMAPos(void)
{
	struct count_info count;

	if (!snd_inited) return 0;

	if (ioctl(audio_fd, SNDCTL_DSP_GETOPTR, &count) == -1) {
		perror(snddevice->string);
		Com_Printf("Uh, sound dead.\n");
		close(audio_fd);
		snd_inited = 0;
		return 0;
	}
	return count.ptr / (dma.samplebits / 8);
}