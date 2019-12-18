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
struct gaudio_snd_dev {int /*<<< orphan*/  filp; } ;
struct gaudio {struct gaudio_snd_dev capture; struct gaudio_snd_dev playback; struct gaudio_snd_dev control; } ;
struct TYPE_2__ {int /*<<< orphan*/  files; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  filp_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gaudio_close_snd_dev(struct gaudio *gau)
{
	struct gaudio_snd_dev	*snd;

	/* Close control device */
	snd = &gau->control;
	if (!IS_ERR(snd->filp))
		filp_close(snd->filp, current->files);

	/* Close PCM playback device and setup substream */
	snd = &gau->playback;
	if (!IS_ERR(snd->filp))
		filp_close(snd->filp, current->files);

	/* Close PCM capture device and setup substream */
	snd = &gau->capture;
	if (!IS_ERR(snd->filp))
		filp_close(snd->filp, current->files);

	return 0;
}