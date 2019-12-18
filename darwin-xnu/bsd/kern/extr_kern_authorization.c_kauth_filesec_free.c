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
typedef  scalar_t__ kauth_filesec_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ KAUTH_FILESEC_NONE ; 
 scalar_t__ KAUTH_FILESEC_WANTED ; 
 int /*<<< orphan*/  M_KAUTH ; 
 int /*<<< orphan*/  panic (char*) ; 

void
kauth_filesec_free(kauth_filesec_t fsp)
{
#ifdef KAUTH_DEBUG_ENABLE
	if (fsp == KAUTH_FILESEC_NONE)
		panic("freeing KAUTH_FILESEC_NONE");
	if (fsp == KAUTH_FILESEC_WANTED)
		panic("freeing KAUTH_FILESEC_WANTED");
#endif
	FREE(fsp, M_KAUTH);
}