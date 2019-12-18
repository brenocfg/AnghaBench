#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/ * soundName; } ;
typedef  TYPE_1__ sfx_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 scalar_t__ MAX_QPATH ; 
 int MAX_SFX ; 
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ *,char const*) ; 
 int S_HashSFXName (char const*) ; 
 TYPE_1__* s_knownSfx ; 
 int s_numSfx ; 
 TYPE_1__** sfxHash ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static sfx_t *S_FindName( const char *name ) {
	int		i;
	int		hash;

	sfx_t	*sfx;

	if (!name) {
		Com_Error (ERR_FATAL, "S_FindName: NULL\n");
	}
	if (!name[0]) {
		Com_Error (ERR_FATAL, "S_FindName: empty name\n");
	}

	if (strlen(name) >= MAX_QPATH) {
		Com_Error (ERR_FATAL, "Sound name too long: %s", name);
	}

	hash = S_HashSFXName(name);

	sfx = sfxHash[hash];
	// see if already loaded
	while (sfx) {
		if (!Q_stricmp(sfx->soundName, name) ) {
			return sfx;
		}
		sfx = sfx->next;
	}

	// find a free sfx
	for (i=0 ; i < s_numSfx ; i++) {
		if (!s_knownSfx[i].soundName[0]) {
			break;
		}
	}

	if (i == s_numSfx) {
		if (s_numSfx == MAX_SFX) {
			Com_Error (ERR_FATAL, "S_FindName: out of sfx_t");
		}
		s_numSfx++;
	}
	
	sfx = &s_knownSfx[i];
	Com_Memset (sfx, 0, sizeof(*sfx));
	strcpy (sfx->soundName, name);

	sfx->next = sfxHash[hash];
	sfxHash[hash] = sfx;

	return sfx;
}