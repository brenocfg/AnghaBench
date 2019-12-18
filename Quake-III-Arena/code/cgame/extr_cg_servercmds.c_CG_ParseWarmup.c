#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int warmupCount; int warmup; } ;
struct TYPE_4__ {int /*<<< orphan*/  countPrepareSound; int /*<<< orphan*/  countPrepareTeamSound; } ;
struct TYPE_5__ {scalar_t__ gametype; TYPE_1__ media; } ;

/* Variables and functions */
 char* CG_ConfigString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHAN_ANNOUNCER ; 
 int /*<<< orphan*/  CS_WARMUP ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ GT_HARVESTER ; 
 int atoi (char const*) ; 
 TYPE_3__ cg ; 
 TYPE_2__ cgs ; 
 int /*<<< orphan*/  trap_S_StartLocalSound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CG_ParseWarmup( void ) {
	const char	*info;
	int			warmup;

	info = CG_ConfigString( CS_WARMUP );

	warmup = atoi( info );
	cg.warmupCount = -1;

	if ( warmup == 0 && cg.warmup ) {

	} else if ( warmup > 0 && cg.warmup <= 0 ) {
#ifdef MISSIONPACK
		if (cgs.gametype >= GT_CTF && cgs.gametype <= GT_HARVESTER) {
			trap_S_StartLocalSound( cgs.media.countPrepareTeamSound, CHAN_ANNOUNCER );
		} else
#endif
		{
			trap_S_StartLocalSound( cgs.media.countPrepareSound, CHAN_ANNOUNCER );
		}
	}

	cg.warmup = warmup;
}