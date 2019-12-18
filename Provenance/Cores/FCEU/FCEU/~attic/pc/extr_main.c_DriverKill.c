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
 int /*<<< orphan*/  KillJoysticks () ; 
 int /*<<< orphan*/  KillKeyboard () ; 
 int /*<<< orphan*/  KillMouse () ; 
 int /*<<< orphan*/  KillSound () ; 
 int /*<<< orphan*/  KillVideo () ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SaveConfig () ; 
 int /*<<< orphan*/  SetSignals (int /*<<< orphan*/ ) ; 
 int inited ; 

__attribute__((used)) static void DriverKill(void)
{
 SaveConfig();

 #ifndef WIN32
 SetSignals(SIG_IGN);
 #endif

 if(inited&2)
  KillJoysticks();
 if(inited&8)
  KillKeyboard();
 if(inited&4)
  KillVideo();
 if(inited&1)
  KillSound();
 if(inited&16)
  KillMouse();
 inited=0;
}