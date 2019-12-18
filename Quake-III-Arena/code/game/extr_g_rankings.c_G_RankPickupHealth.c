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
struct TYPE_2__ {scalar_t__ warmupTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  QGR_KEY_HEALTH ; 
 int /*<<< orphan*/  QGR_KEY_HEALTH_25 ; 
 int /*<<< orphan*/  QGR_KEY_HEALTH_5 ; 
 int /*<<< orphan*/  QGR_KEY_HEALTH_50 ; 
 int /*<<< orphan*/  QGR_KEY_HEALTH_MEGA ; 
 int /*<<< orphan*/  QGR_KEY_HEALTH_TOTAL ; 
 TYPE_1__ level ; 
 int /*<<< orphan*/  trap_RankReportInt (int,int,int /*<<< orphan*/ ,int,int) ; 

void G_RankPickupHealth( int self, int quantity )
{
	if( level.warmupTime != 0 )
	{
		// no reports during warmup period
		return;
	}
	
	trap_RankReportInt( self, -1, QGR_KEY_HEALTH, 1, 1 );
	trap_RankReportInt( self, -1, QGR_KEY_HEALTH_TOTAL, quantity, 1 );

	switch( quantity )
	{
	case 5:
		trap_RankReportInt( self, -1, QGR_KEY_HEALTH_5, 1, 1 );
		break;
	case 25:
		trap_RankReportInt( self, -1, QGR_KEY_HEALTH_25, 1, 1 );
		break;
	case 50:
		trap_RankReportInt( self, -1, QGR_KEY_HEALTH_50, 1, 1 );
		break;
	case 100:
		trap_RankReportInt( self, -1, QGR_KEY_HEALTH_MEGA, 1, 1 );
		break;
	default:
		break;
	}
}