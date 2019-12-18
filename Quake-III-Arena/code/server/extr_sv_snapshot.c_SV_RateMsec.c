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
struct TYPE_4__ {int rate; } ;
typedef  TYPE_1__ client_t ;
struct TYPE_5__ {int integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int HEADER_RATE_BYTES ; 
 TYPE_2__* sv_maxRate ; 

__attribute__((used)) static int SV_RateMsec( client_t *client, int messageSize ) {
	int		rate;
	int		rateMsec;

	// individual messages will never be larger than fragment size
	if ( messageSize > 1500 ) {
		messageSize = 1500;
	}
	rate = client->rate;
	if ( sv_maxRate->integer ) {
		if ( sv_maxRate->integer < 1000 ) {
			Cvar_Set( "sv_MaxRate", "1000" );
		}
		if ( sv_maxRate->integer < rate ) {
			rate = sv_maxRate->integer;
		}
	}
	rateMsec = ( messageSize + HEADER_RATE_BYTES ) * 1000 / rate;

	return rateMsec;
}