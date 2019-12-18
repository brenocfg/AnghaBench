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
typedef  int /*<<< orphan*/  sfxHandle_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  CG_S_REGISTERSOUND ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

sfxHandle_t	trap_S_RegisterSound( const char *sample, qboolean compressed ) {
	return syscall( CG_S_REGISTERSOUND, sample, compressed );
}