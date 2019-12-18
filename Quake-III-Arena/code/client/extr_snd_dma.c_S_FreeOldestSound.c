#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ sndBuffer ;
struct TYPE_6__ {int lastTimeUsed; TYPE_1__* soundData; scalar_t__ inMemory; int /*<<< orphan*/  soundName; } ;
typedef  TYPE_2__ sfx_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*,int /*<<< orphan*/ ) ; 
 int Com_Milliseconds () ; 
 int /*<<< orphan*/  SND_free (TYPE_1__*) ; 
 scalar_t__ qfalse ; 
 TYPE_2__* s_knownSfx ; 
 int s_numSfx ; 

void S_FreeOldestSound() {
	int	i, oldest, used;
	sfx_t	*sfx;
	sndBuffer	*buffer, *nbuffer;

	oldest = Com_Milliseconds();
	used = 0;

	for (i=1 ; i < s_numSfx ; i++) {
		sfx = &s_knownSfx[i];
		if (sfx->inMemory && sfx->lastTimeUsed<oldest) {
			used = i;
			oldest = sfx->lastTimeUsed;
		}
	}

	sfx = &s_knownSfx[used];

	Com_DPrintf("S_FreeOldestSound: freeing sound %s\n", sfx->soundName);

	buffer = sfx->soundData;
	while(buffer != NULL) {
		nbuffer = buffer->next;
		SND_free(buffer);
		buffer = nbuffer;
	}
	sfx->inMemory = qfalse;
	sfx->soundData = NULL;
}