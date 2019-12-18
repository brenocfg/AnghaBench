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
 scalar_t__ W_CheckNumForName (char*) ; 
 scalar_t__ commercial ; 
 int /*<<< orphan*/  ga_completed ; 
 int /*<<< orphan*/  gameaction ; 
 scalar_t__ gamemode ; 
 int secretexit ; 

void G_SecretExitLevel (void) 
{ 
    // IF NO WOLF3D LEVELS, NO SECRET EXIT!
    if ( (gamemode == commercial)
      && (W_CheckNumForName("map31")<0))
	secretexit = false;
    else
	secretexit = true; 
    gameaction = ga_completed; 
}