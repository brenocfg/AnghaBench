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
struct go7007 {int height; int width; int encoder_v_offset; int encoder_h_offset; int gop_size; int /*<<< orphan*/  ipb; int /*<<< orphan*/  format; int /*<<< orphan*/  dvd_mode; int /*<<< orphan*/  modet_enable; int /*<<< orphan*/  closed_gop; scalar_t__ interlace_coding; TYPE_1__* board_info; int /*<<< orphan*/  fps_scale; int /*<<< orphan*/  encoder_h_halve; int /*<<< orphan*/  encoder_v_halve; int /*<<< orphan*/  encoder_subsample; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int sensor_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GO7007_FORMAT_H263 ; 
 int /*<<< orphan*/  GO7007_FORMAT_MJPEG ; 
 int /*<<< orphan*/  GO7007_FORMAT_MPEG1 ; 
 int /*<<< orphan*/  GO7007_FORMAT_MPEG2 ; 
 int /*<<< orphan*/  GO7007_FORMAT_MPEG4 ; 
 int GO7007_SENSOR_CONFIG_MASK ; 
 int GO7007_SENSOR_TV ; 
 int copy_packages (int /*<<< orphan*/ *,int*,int,int) ; 

__attribute__((used)) static int final_package(struct go7007 *go, __le16 *code, int space)
{
	int rows = go->interlace_coding ? go->height / 32 : go->height / 16;
	u16 pack[] = {
		0x8000,
		0,
		0,
		0,
		0,
		0,
		0,
		2,
		((go->board_info->sensor_flags & GO7007_SENSOR_TV) &&
						(!go->interlace_coding) ?
					(1 << 14) | (1 << 9) : 0) |
			((go->encoder_subsample ? 1 : 0) << 8) |
			(go->board_info->sensor_flags &
				GO7007_SENSOR_CONFIG_MASK),
		((go->encoder_v_halve ? 1 : 0) << 14) |
			(go->encoder_v_halve ? rows << 9 : rows << 8) |
			(go->encoder_h_halve ? 1 << 6 : 0) |
			(go->encoder_h_halve ? go->width >> 3 : go->width >> 4),
		(1 << 15) | (go->encoder_v_offset << 6) |
			(1 << 7) | (go->encoder_h_offset >> 2),
		(1 << 6),
		0,
		0,
		((go->fps_scale - 1) << 8) |
			(go->board_info->sensor_flags & GO7007_SENSOR_TV ?
						(1 << 7) : 0) |
			0x41,
		go->ipb ? 0xd4c : 0x36b,
		(rows << 8) | (go->width >> 4),
		go->format == GO7007_FORMAT_MPEG4 ? 0x0404 : 0,
		(1 << 15) | ((go->interlace_coding ? 1 : 0) << 13) |
			((go->closed_gop ? 1 : 0) << 12) |
			((go->format == GO7007_FORMAT_MPEG4 ? 1 : 0) << 11) |
		/*	(1 << 9) |   */
			((go->ipb ? 3 : 0) << 7) |
			((go->modet_enable ? 1 : 0) << 2) |
			((go->dvd_mode ? 1 : 0) << 1) | 1,
		(go->format == GO7007_FORMAT_MPEG1 ? 0x89a0 :
			(go->format == GO7007_FORMAT_MPEG2 ? 0x89a0 :
			(go->format == GO7007_FORMAT_MJPEG ? 0x89a0 :
			(go->format == GO7007_FORMAT_MPEG4 ? 0x8920 :
			(go->format == GO7007_FORMAT_H263 ? 0x8920 : 0))))),
		go->ipb ? 0x1f15 : 0x1f0b,
		go->ipb ? 0x0015 : 0x000b,
		go->ipb ? 0xa800 : 0x5800,
		0xffff,
		0x0020 + 0x034b * 0,
		0x0020 + 0x034b * 1,
		0x0020 + 0x034b * 2,
		0x0020 + 0x034b * 3,
		0x0020 + 0x034b * 4,
		0x0020 + 0x034b * 5,
		go->ipb ? (go->gop_size / 3) : go->gop_size,
		(go->height >> 4) * (go->width >> 4) * 110 / 100,
	};

	return copy_packages(code, pack, 1, space);
}