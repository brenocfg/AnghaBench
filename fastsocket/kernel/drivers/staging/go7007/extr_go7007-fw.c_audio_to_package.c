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
struct go7007 {TYPE_1__* board_info; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int audio_flags; int audio_bclk_div; int audio_main_div; } ;

/* Variables and functions */
 int GO7007_AUDIO_I2S_MASTER ; 
 int GO7007_AUDIO_OKI_MODE ; 
 int copy_packages (int /*<<< orphan*/ *,int*,int,int) ; 

__attribute__((used)) static int audio_to_package(struct go7007 *go, __le16 *code, int space)
{
	int clock_config = ((go->board_info->audio_flags &
				GO7007_AUDIO_I2S_MASTER ? 1 : 0) << 11) |
			((go->board_info->audio_flags &
				GO7007_AUDIO_OKI_MODE ? 1 : 0) << 8) |
			(((go->board_info->audio_bclk_div / 4) - 1) << 4) |
			(go->board_info->audio_main_div - 1);
	u16 pack[] = {
		0x200d,		0,
		0x9002,		0,
		0x9002,		0,
		0x9031,		0,
		0x9032,		0,
		0x9033,		0,
		0x9034,		0,
		0x9035,		0,
		0x9036,		0,
		0x9037,		0,
		0x9040,		0,
		0x9000,		clock_config,
		0x9001,		(go->board_info->audio_flags & 0xffff) |
					(1 << 9),
		0x9000,		((go->board_info->audio_flags &
						GO7007_AUDIO_I2S_MASTER ?
						1 : 0) << 10) |
					clock_config,
		0,		0,
		0,		0,
		0x2005,		0,
		0x9041,		0,
		0x9042,		256,
		0x9043,		0,
		0x9044,		16,
		0x9045,		16,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
		0,		0,
	};

	return copy_packages(code, pack, 2, space);
}