#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  pickup_name; } ;
typedef  TYPE_4__ gitem_t ;
struct TYPE_16__ {int event; scalar_t__ number; int clientNum; } ;
typedef  TYPE_5__ entityState_t ;
struct TYPE_17__ {int /*<<< orphan*/  medkitUsageTime; } ;
typedef  TYPE_6__ clientInfo_t ;
struct TYPE_18__ {TYPE_5__ currentState; } ;
typedef  TYPE_7__ centity_t ;
struct TYPE_20__ {int /*<<< orphan*/  time; TYPE_2__* snap; } ;
struct TYPE_14__ {int /*<<< orphan*/  useInvulnerabilitySound; int /*<<< orphan*/  medkitSound; int /*<<< orphan*/  useNothingSound; } ;
struct TYPE_19__ {TYPE_3__ media; TYPE_6__* clientinfo; } ;
struct TYPE_12__ {scalar_t__ clientNum; } ;
struct TYPE_13__ {TYPE_1__ ps; } ;

/* Variables and functions */
 TYPE_4__* BG_FindItemForHoldable (int) ; 
 int /*<<< orphan*/  BIGCHAR_WIDTH ; 
 int /*<<< orphan*/  CG_CenterPrint (char*,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAN_BODY ; 
 int EV_EVENT_BITS ; 
 int EV_USE_ITEM0 ; 
#define  HI_INVULNERABILITY 133 
#define  HI_KAMIKAZE 132 
#define  HI_MEDKIT 131 
#define  HI_NONE 130 
 int HI_NUM_HOLDABLE ; 
#define  HI_PORTAL 129 
#define  HI_TELEPORTER 128 
 int MAX_CLIENTS ; 
 double SCREEN_HEIGHT ; 
 TYPE_9__ cg ; 
 TYPE_8__ cgs ; 
 int /*<<< orphan*/  trap_S_StartSound (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CG_UseItem( centity_t *cent ) {
	clientInfo_t *ci;
	int			itemNum, clientNum;
	gitem_t		*item;
	entityState_t *es;

	es = &cent->currentState;
	
	itemNum = (es->event & ~EV_EVENT_BITS) - EV_USE_ITEM0;
	if ( itemNum < 0 || itemNum > HI_NUM_HOLDABLE ) {
		itemNum = 0;
	}

	// print a message if the local player
	if ( es->number == cg.snap->ps.clientNum ) {
		if ( !itemNum ) {
			CG_CenterPrint( "No item to use", SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
		} else {
			item = BG_FindItemForHoldable( itemNum );
			CG_CenterPrint( va("Use %s", item->pickup_name), SCREEN_HEIGHT * 0.30, BIGCHAR_WIDTH );
		}
	}

	switch ( itemNum ) {
	default:
	case HI_NONE:
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.useNothingSound );
		break;

	case HI_TELEPORTER:
		break;

	case HI_MEDKIT:
		clientNum = cent->currentState.clientNum;
		if ( clientNum >= 0 && clientNum < MAX_CLIENTS ) {
			ci = &cgs.clientinfo[ clientNum ];
			ci->medkitUsageTime = cg.time;
		}
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.medkitSound );
		break;

#ifdef MISSIONPACK
	case HI_KAMIKAZE:
		break;

	case HI_PORTAL:
		break;
	case HI_INVULNERABILITY:
		trap_S_StartSound (NULL, es->number, CHAN_BODY, cgs.media.useInvulnerabilitySound );
		break;
#endif
	}

}