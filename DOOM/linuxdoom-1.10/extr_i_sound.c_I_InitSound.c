#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sfxinfo_t ;
struct TYPE_2__ {struct TYPE_2__* link; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AFMT_S16_LE ; 
 int /*<<< orphan*/  I_SoundSetTimer (int) ; 
 int MIXBUFFERSIZE ; 
 int NUMSFX ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int SAMPLERATE ; 
 int /*<<< orphan*/  SNDCTL_DSP_GETFMTS ; 
 int /*<<< orphan*/  SNDCTL_DSP_RESET ; 
 int /*<<< orphan*/  SNDCTL_DSP_SETFMT ; 
 int /*<<< orphan*/  SNDCTL_DSP_SETFRAGMENT ; 
 int /*<<< orphan*/  SNDCTL_DSP_SPEED ; 
 int /*<<< orphan*/  SNDCTL_DSP_STEREO ; 
 int SOUND_INTERVAL ; 
 TYPE_1__* S_sfx ; 
 int /*<<< orphan*/  X_OK ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ audio_fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getsfx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lengths ; 
 scalar_t__* mixbuffer ; 
 int /*<<< orphan*/  myioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  popen (char*,char*) ; 
 int /*<<< orphan*/  sndserver ; 
 char* sndserver_filename ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

void
I_InitSound()
{ 
#ifdef SNDSERV
  char buffer[256];
  
  if (getenv("DOOMWADDIR"))
    sprintf(buffer, "%s/%s",
	    getenv("DOOMWADDIR"),
	    sndserver_filename);
  else
    sprintf(buffer, "%s", sndserver_filename);
  
  // start sound process
  if ( !access(buffer, X_OK) )
  {
    strcat(buffer, " -quiet");
    sndserver = popen(buffer, "w");
  }
  else
    fprintf(stderr, "Could not start sound server [%s]\n", buffer);
#else
    
  int i;
  
#ifdef SNDINTR
  fprintf( stderr, "I_SoundSetTimer: %d microsecs\n", SOUND_INTERVAL );
  I_SoundSetTimer( SOUND_INTERVAL );
#endif
    
  // Secure and configure sound device first.
  fprintf( stderr, "I_InitSound: ");
  
  audio_fd = open("/dev/dsp", O_WRONLY);
  if (audio_fd<0)
    fprintf(stderr, "Could not open /dev/dsp\n");
  
                     
  i = 11 | (2<<16);                                           
  myioctl(audio_fd, SNDCTL_DSP_SETFRAGMENT, &i);
  myioctl(audio_fd, SNDCTL_DSP_RESET, 0);
  
  i=SAMPLERATE;
  
  myioctl(audio_fd, SNDCTL_DSP_SPEED, &i);
  
  i=1;
  myioctl(audio_fd, SNDCTL_DSP_STEREO, &i);
  
  myioctl(audio_fd, SNDCTL_DSP_GETFMTS, &i);
  
  if (i&=AFMT_S16_LE)    
    myioctl(audio_fd, SNDCTL_DSP_SETFMT, &i);
  else
    fprintf(stderr, "Could not play signed 16 data\n");

  fprintf(stderr, " configured audio device\n" );

    
  // Initialize external data (all sounds) at start, keep static.
  fprintf( stderr, "I_InitSound: ");
  
  for (i=1 ; i<NUMSFX ; i++)
  { 
    // Alias? Example is the chaingun sound linked to pistol.
    if (!S_sfx[i].link)
    {
      // Load data from WAD file.
      S_sfx[i].data = getsfx( S_sfx[i].name, &lengths[i] );
    }	
    else
    {
      // Previously loaded already?
      S_sfx[i].data = S_sfx[i].link->data;
      lengths[i] = lengths[(S_sfx[i].link - S_sfx)/sizeof(sfxinfo_t)];
    }
  }

  fprintf( stderr, " pre-cached all sound data\n");
  
  // Now initialize mixbuffer with zero.
  for ( i = 0; i< MIXBUFFERSIZE; i++ )
    mixbuffer[i] = 0;
  
  // Finished initialization.
  fprintf(stderr, "I_InitSound: sound module ready\n");
    
#endif
}