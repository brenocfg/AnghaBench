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
struct TYPE_3__ {int /*<<< orphan*/  r; int /*<<< orphan*/  l; } ;
typedef  TYPE_1__ ctr_csnd_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSND_SetPlayState (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csndExecCmds (int) ; 
 int /*<<< orphan*/  csndExit () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  linearFree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctr_csnd_audio_free(void *data)
{
   ctr_csnd_audio_t* ctr = (ctr_csnd_audio_t*)data;

#if 0
   csndExit();
#endif
   CSND_SetPlayState(0x8, 0);
   CSND_SetPlayState(0x9, 0);
   csndExecCmds(false);

   linearFree(ctr->l);
   linearFree(ctr->r);

   free(ctr);
}