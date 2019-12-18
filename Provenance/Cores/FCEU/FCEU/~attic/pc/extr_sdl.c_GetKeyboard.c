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
 char* GUI_GetKeyboard () ; 
 char* KeyState ; 
 char* SDL_GetKeyState (int /*<<< orphan*/ ) ; 

char *GetKeyboard(void)
{
 KeyState=SDL_GetKeyState(0);
 #ifdef EXTGUI
 { char *tmp=GUI_GetKeyboard(); if(tmp) KeyState=tmp; }
 #endif
 return((char *)KeyState);
}