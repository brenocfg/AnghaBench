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
typedef  scalar_t__ u8 ;

/* Variables and functions */
#define  GX_BLEND 132 
 scalar_t__ GX_CA_APREV ; 
 scalar_t__ GX_CA_RASA ; 
 scalar_t__ GX_CA_TEXA ; 
 scalar_t__ GX_CA_ZERO ; 
 scalar_t__ GX_CC_A2 ; 
 scalar_t__ GX_CC_CPREV ; 
 scalar_t__ GX_CC_ONE ; 
 scalar_t__ GX_CC_RASC ; 
 scalar_t__ GX_CC_TEXA ; 
 scalar_t__ GX_CC_TEXC ; 
 scalar_t__ GX_CC_ZERO ; 
 int /*<<< orphan*/  GX_CS_SCALE_1 ; 
#define  GX_DECAL 131 
#define  GX_MODULATE 130 
#define  GX_PASSCLR 129 
#define  GX_REPLACE 128 
 int /*<<< orphan*/  GX_SetTevAlphaIn (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GX_SetTevAlphaOp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_SetTevColorIn (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GX_SetTevColorOp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_TB_ZERO ; 
 int /*<<< orphan*/  GX_TEVPREV ; 
 scalar_t__ GX_TEVSTAGE0 ; 
 int /*<<< orphan*/  GX_TEV_ADD ; 
 int /*<<< orphan*/  GX_TRUE ; 

void GX_SetTevOp(u8 tevstage,u8 mode)
{
	u8 defcolor = GX_CC_RASC;
	u8 defalpha = GX_CA_RASA;

	if(tevstage!=GX_TEVSTAGE0) {
		defcolor = GX_CC_CPREV;
		defalpha = GX_CA_APREV;
	}

	switch(mode) {
		case GX_MODULATE:
			GX_SetTevColorIn(tevstage,GX_CC_ZERO,GX_CC_TEXC,defcolor,GX_CC_ZERO);
			GX_SetTevAlphaIn(tevstage,GX_CA_ZERO,GX_CA_TEXA,defalpha,GX_CA_ZERO);
			break;
		case GX_DECAL:
			GX_SetTevColorIn(tevstage,defcolor,GX_CC_TEXC,GX_CC_TEXA,GX_CC_ZERO);
			GX_SetTevAlphaIn(tevstage,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,defalpha);
			break;
		case GX_BLEND:
			GX_SetTevColorIn(tevstage,defcolor,GX_CC_ONE,GX_CC_TEXC,GX_CC_ZERO);
			GX_SetTevAlphaIn(tevstage,GX_CA_ZERO,GX_CA_TEXA,defalpha,GX_CA_RASA);
			break;
		case GX_REPLACE:
			GX_SetTevColorIn(tevstage,GX_CC_ZERO,GX_CC_ZERO,GX_CC_ZERO,GX_CC_TEXC);
			GX_SetTevAlphaIn(tevstage,GX_CA_ZERO,GX_CA_ZERO,GX_CA_ZERO,GX_CA_TEXA);
			break;
		case GX_PASSCLR:
			GX_SetTevColorIn(tevstage,GX_CC_ZERO,GX_CC_ZERO,GX_CC_ZERO,defcolor);
			GX_SetTevAlphaIn(tevstage,GX_CC_A2,GX_CC_A2,GX_CC_A2,defalpha);
			break;
	}
	GX_SetTevColorOp(tevstage,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,GX_TRUE,GX_TEVPREV);
	GX_SetTevAlphaOp(tevstage,GX_TEV_ADD,GX_TB_ZERO,GX_CS_SCALE_1,GX_TRUE,GX_TEVPREV);
}