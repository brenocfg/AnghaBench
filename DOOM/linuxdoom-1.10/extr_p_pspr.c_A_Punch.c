#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pspdef_t ;
struct TYPE_7__ {TYPE_3__* mo; scalar_t__* powers; } ;
typedef  TYPE_1__ player_t ;
typedef  int angle_t ;
struct TYPE_9__ {int angle; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  MELEERANGE ; 
 int P_AimLineAttack (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_LineAttack (TYPE_3__*,int,int /*<<< orphan*/ ,int,int) ; 
 int P_Random () ; 
 int R_PointToAngle2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_StartSound (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* linetarget ; 
 size_t pw_strength ; 
 int /*<<< orphan*/  sfx_punch ; 

void
A_Punch
( player_t*	player,
  pspdef_t*	psp ) 
{
    angle_t	angle;
    int		damage;
    int		slope;
	
    damage = (P_Random ()%10+1)<<1;

    if (player->powers[pw_strength])	
	damage *= 10;

    angle = player->mo->angle;
    angle += (P_Random()-P_Random())<<18;
    slope = P_AimLineAttack (player->mo, angle, MELEERANGE);
    P_LineAttack (player->mo, angle, MELEERANGE, slope, damage);

    // turn to face target
    if (linetarget)
    {
	S_StartSound (player->mo, sfx_punch);
	player->mo->angle = R_PointToAngle2 (player->mo->x,
					     player->mo->y,
					     linetarget->x,
					     linetarget->y);
    }
}