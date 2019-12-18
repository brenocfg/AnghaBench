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
 int /*<<< orphan*/  EMPTYSTRING ; 
 int /*<<< orphan*/  saveCharIndex ; 
 int /*<<< orphan*/  saveOldString ; 
 int saveSlot ; 
 int saveStringEnter ; 
 scalar_t__** savegamestrings ; 
 int /*<<< orphan*/  strcmp (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 

void M_SaveSelect(int choice)
{
    // we are going to be intercepting all chars
    saveStringEnter = 1;
    
    saveSlot = choice;
    strcpy(saveOldString,savegamestrings[choice]);
    if (!strcmp(savegamestrings[choice],EMPTYSTRING))
	savegamestrings[choice][0] = 0;
    saveCharIndex = strlen(savegamestrings[choice]);
}