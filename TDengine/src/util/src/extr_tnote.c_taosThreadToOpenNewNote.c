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
 int NOTE_FILE_NAME_LEN ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  taosCloseNoteByFd (int) ; 
 int /*<<< orphan*/  taosLockNote (int) ; 
 int taosNoteFd ; 
 int taosNoteFlag ; 
 scalar_t__ taosNoteLines ; 
 char* taosNoteName ; 
 scalar_t__ taosNoteOpenInProgress ; 
 int /*<<< orphan*/  taosNotePrint (char*) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 

void *taosThreadToOpenNewNote(void *param)
{
    char name[NOTE_FILE_NAME_LEN];

    taosNoteFlag ^= 1;
    taosNoteLines = 0;
    sprintf(name, "%s.%d", taosNoteName, taosNoteFlag);

    umask(0);

    int fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
    taosLockNote(fd);
    lseek(fd, 0, SEEK_SET);

    int oldFd = taosNoteFd;
    taosNoteFd = fd;
    taosNoteLines = 0;
    taosNoteOpenInProgress = 0;
    taosNotePrint("===============  new note is opened  =============");

    taosCloseNoteByFd(oldFd);
    return NULL;
}