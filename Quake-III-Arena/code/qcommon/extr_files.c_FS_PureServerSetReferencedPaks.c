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

/* Variables and functions */
 int Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_Argv (int) ; 
 int /*<<< orphan*/  Cmd_TokenizeString (char const*) ; 
 int /*<<< orphan*/ * CopyString (int /*<<< orphan*/ ) ; 
 int MAX_SEARCH_PATHS ; 
 int /*<<< orphan*/  Z_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int fs_numServerReferencedPaks ; 
 int /*<<< orphan*/ ** fs_serverReferencedPakNames ; 
 int /*<<< orphan*/ * fs_serverReferencedPaks ; 

void FS_PureServerSetReferencedPaks( const char *pakSums, const char *pakNames ) {
	int		i, c, d;

	Cmd_TokenizeString( pakSums );

	c = Cmd_Argc();
	if ( c > MAX_SEARCH_PATHS ) {
		c = MAX_SEARCH_PATHS;
	}

	fs_numServerReferencedPaks = c;

	for ( i = 0 ; i < c ; i++ ) {
		fs_serverReferencedPaks[i] = atoi( Cmd_Argv( i ) );
	}

	for ( i = 0 ; i < c ; i++ ) {
		if (fs_serverReferencedPakNames[i]) {
			Z_Free(fs_serverReferencedPakNames[i]);
		}
		fs_serverReferencedPakNames[i] = NULL;
	}
	if ( pakNames && *pakNames ) {
		Cmd_TokenizeString( pakNames );

		d = Cmd_Argc();
		if ( d > MAX_SEARCH_PATHS ) {
			d = MAX_SEARCH_PATHS;
		}

		for ( i = 0 ; i < d ; i++ ) {
			fs_serverReferencedPakNames[i] = CopyString( Cmd_Argv( i ) );
		}
	}
}