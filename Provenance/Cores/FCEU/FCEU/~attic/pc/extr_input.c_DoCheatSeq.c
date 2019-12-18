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
 int /*<<< orphan*/  CurGame ; 
 int /*<<< orphan*/  DoConsoleCheatConfig () ; 
 int /*<<< orphan*/  InitKeyboard () ; 
 int /*<<< orphan*/  InitVideo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KillKeyboard () ; 
 int /*<<< orphan*/  KillVideo () ; 
 int /*<<< orphan*/  SilenceSound (int) ; 

__attribute__((used)) static void DoCheatSeq(void)
{
 #if defined(DOS) || defined(SDL)
 SilenceSound(1);
 #endif
 KillKeyboard();
 KillVideo();

 DoConsoleCheatConfig();
 InitVideo(CurGame);
 InitKeyboard();
 #if defined(DOS) || defined(SDL)
 SilenceSound(0);
 #endif
}