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
typedef  int /*<<< orphan*/  cMsg ;
struct TYPE_2__ {int /*<<< orphan*/  serverId; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_AddReliableCommand (char*) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*) ; 
 char* FS_ReferencedPakPureChecksums () ; 
 int MAX_INFO_VALUE ; 
 int /*<<< orphan*/  Q_strcat (char*,int,char const*) ; 
 TYPE_1__ cl ; 
 char const* va (char*,int /*<<< orphan*/ ) ; 

void CL_SendPureChecksums( void ) {
	const char *pChecksums;
	char cMsg[MAX_INFO_VALUE];
	int i;

	// if we are pure we need to send back a command with our referenced pk3 checksums
	pChecksums = FS_ReferencedPakPureChecksums();

	// "cp"
	// "Yf"
	Com_sprintf(cMsg, sizeof(cMsg), "Yf ");
	Q_strcat(cMsg, sizeof(cMsg), va("%d ", cl.serverId) );
	Q_strcat(cMsg, sizeof(cMsg), pChecksums);
	for (i = 0; i < 2; i++) {
		cMsg[i] += 10;
	}
	CL_AddReliableCommand( cMsg );
}