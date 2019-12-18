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
 int /*<<< orphan*/  CL_Shutdown () ; 
 int FNDELAY ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  Sys_Exit (int /*<<< orphan*/ ) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void Sys_Quit (void) {
  CL_Shutdown ();
  fcntl (0, F_SETFL, fcntl (0, F_GETFL, 0) & ~FNDELAY);
  Sys_Exit(0);
}