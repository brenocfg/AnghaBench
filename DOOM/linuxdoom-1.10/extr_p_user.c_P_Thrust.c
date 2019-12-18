#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* mo; } ;
typedef  TYPE_2__ player_t ;
typedef  int /*<<< orphan*/  fixed_t ;
typedef  size_t angle_t ;
struct TYPE_4__ {int /*<<< orphan*/  momy; int /*<<< orphan*/  momx; } ;

/* Variables and functions */
 size_t ANGLETOFINESHIFT ; 
 scalar_t__ FixedMul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * finecosine ; 
 int /*<<< orphan*/ * finesine ; 

void
P_Thrust
( player_t*	player,
  angle_t	angle,
  fixed_t	move ) 
{
    angle >>= ANGLETOFINESHIFT;
    
    player->mo->momx += FixedMul(move,finecosine[angle]); 
    player->mo->momy += FixedMul(move,finesine[angle]);
}