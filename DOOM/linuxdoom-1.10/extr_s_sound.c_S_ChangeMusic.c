#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int /*<<< orphan*/  handle; void* data; scalar_t__ lumpnum; } ;
typedef  TYPE_1__ musicinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*,int) ; 
 int /*<<< orphan*/  I_PlaySong (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I_RegisterSong (void*) ; 
 int NUMMUSIC ; 
 int /*<<< orphan*/  PU_MUSIC ; 
 int /*<<< orphan*/  S_StopMusic () ; 
 TYPE_1__* S_music ; 
 scalar_t__ W_CacheLumpNum (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ W_GetNumForName (char*) ; 
 int mus_None ; 
 TYPE_1__* mus_playing ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void
S_ChangeMusic
( int			musicnum,
  int			looping )
{
    musicinfo_t*	music;
    char		namebuf[9];

    if ( (musicnum <= mus_None)
	 || (musicnum >= NUMMUSIC) )
    {
	I_Error("Bad music number %d", musicnum);
    }
    else
	music = &S_music[musicnum];

    if (mus_playing == music)
	return;

    // shutdown old music
    S_StopMusic();

    // get lumpnum if neccessary
    if (!music->lumpnum)
    {
	sprintf(namebuf, "d_%s", music->name);
	music->lumpnum = W_GetNumForName(namebuf);
    }

    // load & register it
    music->data = (void *) W_CacheLumpNum(music->lumpnum, PU_MUSIC);
    music->handle = I_RegisterSong(music->data);

    // play it
    I_PlaySong(music->handle, looping);

    mus_playing = music;
}