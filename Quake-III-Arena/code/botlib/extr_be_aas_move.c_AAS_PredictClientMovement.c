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
typedef  int /*<<< orphan*/  vec3_t ;
struct aas_clientmove_s {int dummy; } ;

/* Variables and functions */
 int AAS_ClientMovementPrediction (struct aas_clientmove_s*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,float,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int AAS_PredictClientMovement(struct aas_clientmove_s *move,
								int entnum, vec3_t origin,
								int presencetype, int onground,
								vec3_t velocity, vec3_t cmdmove,
								int cmdframes,
								int maxframes, float frametime,
								int stopevent, int stopareanum, int visualize)
{
	vec3_t mins, maxs;
	return AAS_ClientMovementPrediction(move, entnum, origin, presencetype, onground,
										velocity, cmdmove, cmdframes, maxframes,
										frametime, stopevent, stopareanum,
										mins, maxs, visualize);
}