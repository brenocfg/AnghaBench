#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pspdef_t ;
struct TYPE_3__ {int /*<<< orphan*/  mo; } ;
typedef  TYPE_1__ player_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_StartSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfx_dbload ; 

void
A_LoadShotgun2
( player_t*	player,
  pspdef_t*	psp )
{
    S_StartSound (player->mo, sfx_dbload);
}