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
typedef  int u16 ;
struct go7007 {int fps_scale; int sensor_framerate; TYPE_1__* board_info; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int audio_rate; } ;

/* Variables and functions */
 int copy_packages (int /*<<< orphan*/ *,int*,int,int) ; 
 int relative_prime (int,int) ; 

__attribute__((used)) static int avsync_to_package(struct go7007 *go, __le16 *code, int space)
{
	int arate = go->board_info->audio_rate * 1001 * go->fps_scale;
	int ratio = arate / go->sensor_framerate;
	int adjratio = ratio * 215 / 100;
	int rprime = relative_prime(go->sensor_framerate,
					arate % go->sensor_framerate);
	int f1 = (arate % go->sensor_framerate) / rprime;
	int f2 = (go->sensor_framerate - arate % go->sensor_framerate) / rprime;
	u16 pack[] = {
		0x200e,		0,
		0xbf98,		(u16)((-adjratio) & 0xffff),
		0xbf99,		(u16)((-adjratio) >> 16),
		0xbf92,		0,
		0xbf93,		0,
		0xbff4,		f1 > f2 ? f1 : f2,
		0xbff5,		f1 < f2 ? f1 : f2,
		0xbff6,		f1 < f2 ? ratio : ratio + 1,
		0xbff7,		f1 > f2 ? ratio : ratio + 1,
		0xbff8,		0,
		0xbff9,		0,
		0xbffa,		adjratio & 0xffff,
		0xbffb,		adjratio >> 16,
		0xbf94,		0,
		0xbf95,		0,
		0,		0,
	};

	return copy_packages(code, pack, 1, space);
}