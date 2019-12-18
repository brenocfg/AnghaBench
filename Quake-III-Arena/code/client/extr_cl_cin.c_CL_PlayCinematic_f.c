#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/ * buf; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CA_CINEMATIC ; 
 scalar_t__ CIN_PlayCinematic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CIN_hold ; 
 int CIN_loop ; 
 int CIN_system ; 
 scalar_t__ CL_handle ; 
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_DPrintf (char*) ; 
 scalar_t__ FMV_PLAY ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  SCREEN_HEIGHT ; 
 int /*<<< orphan*/  SCREEN_WIDTH ; 
 int /*<<< orphan*/  SCR_RunCinematic () ; 
 int /*<<< orphan*/  SCR_StopCinematic () ; 
 int /*<<< orphan*/  S_StopAllSounds () ; 
 TYPE_2__* cinTable ; 
 TYPE_1__ cls ; 
 size_t currentHandle ; 
 int /*<<< orphan*/  qfalse ; 

void CL_PlayCinematic_f(void) {
	char	*arg, *s;
	qboolean	holdatend;
	int bits = CIN_system;

	Com_DPrintf("CL_PlayCinematic_f\n");
	if (cls.state == CA_CINEMATIC) {
		SCR_StopCinematic();
	}

	arg = Cmd_Argv( 1 );
	s = Cmd_Argv(2);

	holdatend = qfalse;
	if ((s && s[0] == '1') || Q_stricmp(arg,"demoend.roq")==0 || Q_stricmp(arg,"end.roq")==0) {
		bits |= CIN_hold;
	}
	if (s && s[0] == '2') {
		bits |= CIN_loop;
	}

	S_StopAllSounds ();

	CL_handle = CIN_PlayCinematic( arg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bits );
	if (CL_handle >= 0) {
		do {
			SCR_RunCinematic();
		} while (cinTable[currentHandle].buf == NULL && cinTable[currentHandle].status == FMV_PLAY);		// wait for first frame (load codebook and sound)
	}
}