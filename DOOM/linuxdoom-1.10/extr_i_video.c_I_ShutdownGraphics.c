#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  shmid; int /*<<< orphan*/  shmaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  I_Error (char*) ; 
 int /*<<< orphan*/  XShmDetach (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  X_display ; 
 TYPE_2__ X_shminfo ; 
 TYPE_1__* image ; 
 int /*<<< orphan*/  shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmdt (int /*<<< orphan*/ ) ; 

void I_ShutdownGraphics(void)
{
  // Detach from X server
  if (!XShmDetach(X_display, &X_shminfo))
	    I_Error("XShmDetach() failed in I_ShutdownGraphics()");

  // Release shared memory.
  shmdt(X_shminfo.shmaddr);
  shmctl(X_shminfo.shmid, IPC_RMID, 0);

  // Paranoia.
  image->data = NULL;
}