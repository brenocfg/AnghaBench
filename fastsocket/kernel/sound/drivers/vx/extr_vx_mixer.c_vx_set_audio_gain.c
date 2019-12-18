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
struct vx_core {int** audio_gain; } ;
struct vx_audio_level {int has_level; int level; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vx_audio_level*,int /*<<< orphan*/ ,int) ; 
 int vx_adjust_audio_level (struct vx_core*,int,int,struct vx_audio_level*) ; 

__attribute__((used)) static int vx_set_audio_gain(struct vx_core *chip, int audio, int capture, int level)
{
	struct vx_audio_level info;

	memset(&info, 0, sizeof(info));
	info.has_level = 1;
	info.level = level;
	chip->audio_gain[capture][audio] = level;
	return vx_adjust_audio_level(chip, audio, capture, &info);
}