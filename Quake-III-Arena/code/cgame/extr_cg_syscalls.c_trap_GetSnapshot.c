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
typedef  int /*<<< orphan*/  snapshot_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  CG_GETSNAPSHOT ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

qboolean	trap_GetSnapshot( int snapshotNumber, snapshot_t *snapshot ) {
	return syscall( CG_GETSNAPSHOT, snapshotNumber, snapshot );
}