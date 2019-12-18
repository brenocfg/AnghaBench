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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct zoran {int norm; TYPE_1__ card; } ;
typedef  enum zoran_codec_mode { ____Placeholder_zoran_codec_mode } zoran_codec_mode ;

/* Variables and functions */
#define  BUZ_MODE_IDLE 130 
#define  BUZ_MODE_MOTION_COMPRESS 129 
#define  BUZ_MODE_MOTION_DECOMPRESS 128 
 int /*<<< orphan*/  LML33R10 ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int /*<<< orphan*/  ZR36057_VFEHCR ; 
 int /*<<< orphan*/  ZR36057_VFESPFR ; 
 int /*<<< orphan*/  ZR36057_VFESPFR_ExtFl ; 
 int /*<<< orphan*/  btand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zr36057_adjust_vfe (struct zoran          *zr,
		    enum zoran_codec_mode  mode)
{
	u32 reg;

	switch (mode) {
	case BUZ_MODE_MOTION_DECOMPRESS:
		btand(~ZR36057_VFESPFR_ExtFl, ZR36057_VFESPFR);
		reg = btread(ZR36057_VFEHCR);
		if ((reg & (1 << 10)) && zr->card.type != LML33R10) {
			reg += ((1 << 10) | 1);
		}
		btwrite(reg, ZR36057_VFEHCR);
		break;
	case BUZ_MODE_MOTION_COMPRESS:
	case BUZ_MODE_IDLE:
	default:
		if ((zr->norm & V4L2_STD_NTSC) ||
		    (zr->card.type == LML33R10 &&
		     (zr->norm & V4L2_STD_PAL)))
			btand(~ZR36057_VFESPFR_ExtFl, ZR36057_VFESPFR);
		else
			btor(ZR36057_VFESPFR_ExtFl, ZR36057_VFESPFR);
		reg = btread(ZR36057_VFEHCR);
		if (!(reg & (1 << 10)) && zr->card.type != LML33R10) {
			reg -= ((1 << 10) | 1);
		}
		btwrite(reg, ZR36057_VFEHCR);
		break;
	}
}