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
 int /*<<< orphan*/  CL_Vid_Restart_f () ; 
 int /*<<< orphan*/  S_Init () ; 
 int /*<<< orphan*/  S_Shutdown () ; 

void CL_Snd_Restart_f( void ) {
	S_Shutdown();
	S_Init();

	CL_Vid_Restart_f();
}