#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hWnd; } ;
struct TYPE_6__ {TYPE_1__* lpVtbl; } ;
struct TYPE_5__ {scalar_t__ (* SetCooperativeLevel ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  DSSCL_PRIORITY ; 
 scalar_t__ DS_OK ; 
 int /*<<< orphan*/  SNDDMA_Shutdown () ; 
 TYPE_4__ g_wv ; 
 TYPE_2__* pDS ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SNDDMA_Activate( void ) {
	if ( !pDS ) {
		return;
	}

	if ( DS_OK != pDS->lpVtbl->SetCooperativeLevel( pDS, g_wv.hWnd, DSSCL_PRIORITY ) )	{
		Com_Printf ("sound SetCooperativeLevel failed\n");
		SNDDMA_Shutdown ();
	}
}