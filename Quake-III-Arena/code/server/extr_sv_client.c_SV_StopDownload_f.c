#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* downloadName; } ;
typedef  TYPE_1__ client_t ;
struct TYPE_7__ {int clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  SV_CloseDownload (TYPE_1__*) ; 
 TYPE_2__ svs ; 

void SV_StopDownload_f( client_t *cl ) {
	if (*cl->downloadName)
		Com_DPrintf( "clientDownload: %d : file \"%s\" aborted\n", cl - svs.clients, cl->downloadName );

	SV_CloseDownload( cl );
}