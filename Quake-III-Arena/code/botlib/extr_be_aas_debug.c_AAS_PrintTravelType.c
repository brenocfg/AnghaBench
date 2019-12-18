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
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int TRAVELTYPE_MASK ; 
#define  TRAVEL_BARRIERJUMP 143 
#define  TRAVEL_BFGJUMP 142 
#define  TRAVEL_CROUCH 141 
#define  TRAVEL_ELEVATOR 140 
#define  TRAVEL_FUNCBOB 139 
#define  TRAVEL_GRAPPLEHOOK 138 
#define  TRAVEL_INVALID 137 
#define  TRAVEL_JUMP 136 
#define  TRAVEL_JUMPPAD 135 
#define  TRAVEL_LADDER 134 
#define  TRAVEL_ROCKETJUMP 133 
#define  TRAVEL_SWIM 132 
#define  TRAVEL_TELEPORT 131 
#define  TRAVEL_WALK 130 
#define  TRAVEL_WALKOFFLEDGE 129 
#define  TRAVEL_WATERJUMP 128 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 

void AAS_PrintTravelType(int traveltype)
{
#ifdef DEBUG
	char *str;
	//
	switch(traveltype & TRAVELTYPE_MASK)
	{
		case TRAVEL_INVALID: str = "TRAVEL_INVALID"; break;
		case TRAVEL_WALK: str = "TRAVEL_WALK"; break;
		case TRAVEL_CROUCH: str = "TRAVEL_CROUCH"; break;
		case TRAVEL_BARRIERJUMP: str = "TRAVEL_BARRIERJUMP"; break;
		case TRAVEL_JUMP: str = "TRAVEL_JUMP"; break;
		case TRAVEL_LADDER: str = "TRAVEL_LADDER"; break;
		case TRAVEL_WALKOFFLEDGE: str = "TRAVEL_WALKOFFLEDGE"; break;
		case TRAVEL_SWIM: str = "TRAVEL_SWIM"; break;
		case TRAVEL_WATERJUMP: str = "TRAVEL_WATERJUMP"; break;
		case TRAVEL_TELEPORT: str = "TRAVEL_TELEPORT"; break;
		case TRAVEL_ELEVATOR: str = "TRAVEL_ELEVATOR"; break;
		case TRAVEL_ROCKETJUMP: str = "TRAVEL_ROCKETJUMP"; break;
		case TRAVEL_BFGJUMP: str = "TRAVEL_BFGJUMP"; break;
		case TRAVEL_GRAPPLEHOOK: str = "TRAVEL_GRAPPLEHOOK"; break;
		case TRAVEL_JUMPPAD: str = "TRAVEL_JUMPPAD"; break;
		case TRAVEL_FUNCBOB: str = "TRAVEL_FUNCBOB"; break;
		default: str = "UNKNOWN TRAVEL TYPE"; break;
	} //end switch
	botimport.Print(PRT_MESSAGE, "%s", str);
#endif
}