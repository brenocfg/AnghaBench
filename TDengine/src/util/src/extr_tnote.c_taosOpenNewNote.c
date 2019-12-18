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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int taosNoteFd ; 
 scalar_t__ taosNoteLines ; 
 scalar_t__ taosNoteMaxLines ; 
 int /*<<< orphan*/  taosNoteMutex ; 
 int taosNoteOpenInProgress ; 
 int /*<<< orphan*/  taosNotePrint (char*) ; 
 int /*<<< orphan*/  taosThreadToOpenNewNote ; 

int taosOpenNewNote()
{
    pthread_mutex_lock(&taosNoteMutex);

    if (taosNoteLines > taosNoteMaxLines && taosNoteOpenInProgress == 0) {
        taosNoteOpenInProgress = 1;

        taosNotePrint("===============  open new note  ==================");
        pthread_t pattern;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

        pthread_create(&pattern, &attr, taosThreadToOpenNewNote, NULL);
        pthread_attr_destroy(&attr);
    }

    pthread_mutex_unlock(&taosNoteMutex);

    return taosNoteFd;
}