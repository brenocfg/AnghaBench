#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ppbufw; int /*<<< orphan*/  wf; int /*<<< orphan*/  ppbufsec; scalar_t__ ToWritePos; } ;
typedef  int DWORD ;
typedef  TYPE_1__ DSFobby ;

/* Variables and functions */
 int /*<<< orphan*/  DSBPLAY_LOOPING ; 
 int DSBSTATUS_BUFFERLOST ; 
 int DSBSTATUS_PLAYING ; 
 int /*<<< orphan*/  IDirectSoundBuffer_GetStatus (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Play (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_SetCurrentPosition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_SetFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CheckStatus(DSFobby *tmp)
{
 DWORD status=0;

 IDirectSoundBuffer_GetStatus(tmp->ppbufw, &status);
 if(status&DSBSTATUS_BUFFERLOST)
  IDirectSoundBuffer_Restore(tmp->ppbufw);

 if(!(status&DSBSTATUS_PLAYING))
 {
  tmp->ToWritePos=0;
  IDirectSoundBuffer_SetCurrentPosition(tmp->ppbufsec,0);
  IDirectSoundBuffer_SetFormat(tmp->ppbufw,&tmp->wf);
  IDirectSoundBuffer_Play(tmp->ppbufw,0,0,DSBPLAY_LOOPING);
 }
}