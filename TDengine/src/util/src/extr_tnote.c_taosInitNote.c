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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* logDir ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  taosNotePrint (char*) ; 
 scalar_t__ taosOpenNoteWithMaxLines (char*,int,int) ; 

void taosInitNote(int numOfNoteLines, int maxNotes)
{
    char temp[128] = { 0 };
    sprintf(temp, "%s/taosnote", logDir);
    if (taosOpenNoteWithMaxLines(temp, numOfNoteLines, maxNotes) < 0)
        fprintf(stderr, "failed to init note file\n");

    taosNotePrint("==================================================");
    taosNotePrint("===================  new note  ===================");
    taosNotePrint("==================================================");
}