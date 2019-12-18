#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  netchan_t ;
struct TYPE_5__ {scalar_t__ cursize; } ;
typedef  TYPE_1__ msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_Netchan_Decode (TYPE_1__*) ; 
 int Netchan_Process (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  newsize ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean CL_Netchan_Process( netchan_t *chan, msg_t *msg ) {
	int ret;

	ret = Netchan_Process( chan, msg );
	if (!ret)
		return qfalse;
	CL_Netchan_Decode( msg );
	newsize += msg->cursize;
	return qtrue;
}