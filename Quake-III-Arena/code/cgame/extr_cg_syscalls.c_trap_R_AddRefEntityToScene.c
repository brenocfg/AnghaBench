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
typedef  int /*<<< orphan*/  refEntity_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_R_ADDREFENTITYTOSCENE ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void	trap_R_AddRefEntityToScene( const refEntity_t *re ) {
	syscall( CG_R_ADDREFENTITYTOSCENE, re );
}