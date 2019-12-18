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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASND_Init () ; 
 scalar_t__ Bg_music_ogg ; 
 int /*<<< orphan*/  Bg_music_ogg_size ; 
 char* DEFAULT_PATH ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memalign (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 

void gx_audio_Init(void)
{
  /* Initialize AUDIO processing library (ASNDLIB) */
  /* AUDIO & DSP hardware are initialized */
  /* Default samplerate is set to 48kHz */
  ASND_Init();

  /* Load background music from FAT device */
  char fname[MAXPATHLEN];
  sprintf(fname,"%s/Bg_music.ogg",DEFAULT_PATH);
  FILE *f = fopen(fname,"rb");
  if (f)
  {
    struct stat filestat;
    stat(fname, &filestat);
    Bg_music_ogg_size = filestat.st_size;
    Bg_music_ogg = memalign(32,Bg_music_ogg_size);
    if (Bg_music_ogg)
    {
      fread(Bg_music_ogg,1,Bg_music_ogg_size,f);
    }
    fclose(f);
  }
}