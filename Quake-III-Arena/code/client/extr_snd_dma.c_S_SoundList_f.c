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
struct TYPE_3__ {int soundLength; size_t soundCompressionMethod; size_t inMemory; int /*<<< orphan*/  soundName; } ;
typedef  TYPE_1__ sfx_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int,...) ; 
 int /*<<< orphan*/  S_DisplayFreeMemory () ; 
 TYPE_1__* s_knownSfx ; 
 int s_numSfx ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void S_SoundList_f( void ) {
	int		i;
	sfx_t	*sfx;
	int		size, total;
	char	type[4][16];
	char	mem[2][16];

	strcpy(type[0], "16bit");
	strcpy(type[1], "adpcm");
	strcpy(type[2], "daub4");
	strcpy(type[3], "mulaw");
	strcpy(mem[0], "paged out");
	strcpy(mem[1], "resident ");
	total = 0;
	for (sfx=s_knownSfx, i=0 ; i<s_numSfx ; i++, sfx++) {
		size = sfx->soundLength;
		total += size;
		Com_Printf("%6i[%s] : %s[%s]\n", size, type[sfx->soundCompressionMethod], sfx->soundName, mem[sfx->inMemory] );
	}
	Com_Printf ("Total resident: %i\n", total);
	S_DisplayFreeMemory();
}