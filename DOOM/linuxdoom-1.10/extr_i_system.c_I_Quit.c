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
 int /*<<< orphan*/  D_QuitNetGame () ; 
 int /*<<< orphan*/  I_ShutdownGraphics () ; 
 int /*<<< orphan*/  I_ShutdownMusic () ; 
 int /*<<< orphan*/  I_ShutdownSound () ; 
 int /*<<< orphan*/  M_SaveDefaults () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

void I_Quit (void)
{
    D_QuitNetGame ();
    I_ShutdownSound();
    I_ShutdownMusic();
    M_SaveDefaults ();
    I_ShutdownGraphics();
    exit(0);
}