#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ssb_sprom {int antswitch; int ant_available_bg; int ant_available_a; } ;
struct brcms_c_info {TYPE_4__* hw; TYPE_2__* pub; } ;
struct antsel_info {int antsel_avail; int antsel_antswitch; int /*<<< orphan*/  antcfg_cur; int /*<<< orphan*/  antcfg_11n; void* antsel_type; TYPE_2__* pub; struct brcms_c_info* wlc; } ;
struct TYPE_8__ {TYPE_3__* d11core; } ;
struct TYPE_7__ {TYPE_1__* bus; } ;
struct TYPE_6__ {int sromrev; int boardflags2; } ;
struct TYPE_5__ {struct ssb_sprom sprom; } ;

/* Variables and functions */
 void* ANTSEL_2x3 ; 
 void* ANTSEL_2x4 ; 
 void* ANTSEL_NA ; 
#define  ANTSWITCH_TYPE_1 130 
#define  ANTSWITCH_TYPE_2 129 
#define  ANTSWITCH_TYPE_3 128 
 int BFL2_2X4_DIV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  brcms_b_antsel_type_set (TYPE_4__*,void*) ; 
 int /*<<< orphan*/  brcms_c_antsel_init_cfg (struct antsel_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  brcms_err (TYPE_3__*,char*) ; 
 struct antsel_info* kzalloc (int,int /*<<< orphan*/ ) ; 

struct antsel_info *brcms_c_antsel_attach(struct brcms_c_info *wlc)
{
	struct antsel_info *asi;
	struct ssb_sprom *sprom = &wlc->hw->d11core->bus->sprom;

	asi = kzalloc(sizeof(struct antsel_info), GFP_ATOMIC);
	if (!asi)
		return NULL;

	asi->wlc = wlc;
	asi->pub = wlc->pub;
	asi->antsel_type = ANTSEL_NA;
	asi->antsel_avail = false;
	asi->antsel_antswitch = sprom->antswitch;

	if ((asi->pub->sromrev >= 4) && (asi->antsel_antswitch != 0)) {
		switch (asi->antsel_antswitch) {
		case ANTSWITCH_TYPE_1:
		case ANTSWITCH_TYPE_2:
		case ANTSWITCH_TYPE_3:
			/* 4321/2 board with 2x3 switch logic */
			asi->antsel_type = ANTSEL_2x3;
			/* Antenna selection availability */
			if ((sprom->ant_available_bg == 7) ||
			    (sprom->ant_available_a == 7)) {
				asi->antsel_avail = true;
			} else if (
				sprom->ant_available_bg == 3 ||
				sprom->ant_available_a == 3) {
				asi->antsel_avail = false;
			} else {
				asi->antsel_avail = false;
				brcms_err(wlc->hw->d11core,
					  "antsel_attach: 2o3 "
					  "board cfg invalid\n");
			}

			break;
		default:
			break;
		}
	} else if ((asi->pub->sromrev == 4) &&
		   (sprom->ant_available_bg == 7) &&
		   (sprom->ant_available_a == 0)) {
		/* hack to match old 4321CB2 cards with 2of3 antenna switch */
		asi->antsel_type = ANTSEL_2x3;
		asi->antsel_avail = true;
	} else if (asi->pub->boardflags2 & BFL2_2X4_DIV) {
		asi->antsel_type = ANTSEL_2x4;
		asi->antsel_avail = true;
	}

	/* Set the antenna selection type for the low driver */
	brcms_b_antsel_type_set(wlc->hw, asi->antsel_type);

	/* Init (auto/manual) antenna selection */
	brcms_c_antsel_init_cfg(asi, &asi->antcfg_11n, true);
	brcms_c_antsel_init_cfg(asi, &asi->antcfg_cur, true);

	return asi;
}