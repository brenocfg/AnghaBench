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
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_4__ {int challenge; int /*<<< orphan*/  adr; int /*<<< orphan*/  pingTime; } ;
struct TYPE_3__ {TYPE_2__* challenges; int /*<<< orphan*/  time; int /*<<< orphan*/  authorizeAddress; } ;

/* Variables and functions */
 char* Cmd_Argv (int) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 scalar_t__ Cvar_VariableValue (char*) ; 
 int MAX_CHALLENGES ; 
 int /*<<< orphan*/  NET_CompareBaseAdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_OutOfBandPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  NS_SERVER ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 TYPE_1__ svs ; 

void SV_AuthorizeIpPacket( netadr_t from ) {
	int		challenge;
	int		i;
	char	*s;
	char	*r;
	char	ret[1024];

	if ( !NET_CompareBaseAdr( from, svs.authorizeAddress ) ) {
		Com_Printf( "SV_AuthorizeIpPacket: not from authorize server\n" );
		return;
	}

	challenge = atoi( Cmd_Argv( 1 ) );

	for (i = 0 ; i < MAX_CHALLENGES ; i++) {
		if ( svs.challenges[i].challenge == challenge ) {
			break;
		}
	}
	if ( i == MAX_CHALLENGES ) {
		Com_Printf( "SV_AuthorizeIpPacket: challenge not found\n" );
		return;
	}

	// send a packet back to the original client
	svs.challenges[i].pingTime = svs.time;
	s = Cmd_Argv( 2 );
	r = Cmd_Argv( 3 );			// reason

	if ( !Q_stricmp( s, "demo" ) ) {
		if ( Cvar_VariableValue( "fs_restrict" ) ) {
			// a demo client connecting to a demo server
			NET_OutOfBandPrint( NS_SERVER, svs.challenges[i].adr, 
				"challengeResponse %i", svs.challenges[i].challenge );
			return;
		}
		// they are a demo client trying to connect to a real server
		NET_OutOfBandPrint( NS_SERVER, svs.challenges[i].adr, "print\nServer is not a demo server\n" );
		// clear the challenge record so it won't timeout and let them through
		Com_Memset( &svs.challenges[i], 0, sizeof( svs.challenges[i] ) );
		return;
	}
	if ( !Q_stricmp( s, "accept" ) ) {
		NET_OutOfBandPrint( NS_SERVER, svs.challenges[i].adr, 
			"challengeResponse %i", svs.challenges[i].challenge );
		return;
	}
	if ( !Q_stricmp( s, "unknown" ) ) {
		if (!r) {
			NET_OutOfBandPrint( NS_SERVER, svs.challenges[i].adr, "print\nAwaiting CD key authorization\n" );
		} else {
			sprintf(ret, "print\n%s\n", r);
			NET_OutOfBandPrint( NS_SERVER, svs.challenges[i].adr, ret );
		}
		// clear the challenge record so it won't timeout and let them through
		Com_Memset( &svs.challenges[i], 0, sizeof( svs.challenges[i] ) );
		return;
	}

	// authorization failed
	if (!r) {
		NET_OutOfBandPrint( NS_SERVER, svs.challenges[i].adr, "print\nSomeone is using this CD Key\n" );
	} else {
		sprintf(ret, "print\n%s\n", r);
		NET_OutOfBandPrint( NS_SERVER, svs.challenges[i].adr, ret );
	}

	// clear the challenge record so it won't timeout and let them through
	Com_Memset( &svs.challenges[i], 0, sizeof( svs.challenges[i] ) );
}