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
 int NUMSFX ; 
 int /*<<< orphan*/  R_OK ; 
 TYPE_1__* S_sfx ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getsfx (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__* lengths ; 
 scalar_t__ longsound ; 
 char* malloc (scalar_t__) ; 
 int numsounds ; 
 int /*<<< orphan*/  openwad (char*) ; 
 scalar_t__ snd_verbose ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void
grabdata
( int		c,
  char**	v )
{
    int		i;
    char*	name;
    char*	doom1wad;
    char*	doomwad;
    char*	doomuwad;
    char*	doom2wad;
    char*	doom2fwad;
    // Now where are TNT and Plutonia. Yuck.
    
    //	char *home;
    char*	doomwaddir;

    doomwaddir = getenv("DOOMWADDIR");

    if (!doomwaddir)
	doomwaddir = ".";

    doom1wad = malloc(strlen(doomwaddir)+1+9+1);
    sprintf(doom1wad, "%s/doom1.wad", doomwaddir);

    doom2wad = malloc(strlen(doomwaddir)+1+9+1);
    sprintf(doom2wad, "%s/doom2.wad", doomwaddir);

    doom2fwad = malloc(strlen(doomwaddir)+1+10+1);
    sprintf(doom2fwad, "%s/doom2f.wad", doomwaddir);
    
    doomuwad = malloc(strlen(doomwaddir)+1+8+1);
    sprintf(doomuwad, "%s/doomu.wad", doomwaddir);
    
    doomwad = malloc(strlen(doomwaddir)+1+8+1);
    sprintf(doomwad, "%s/doom.wad", doomwaddir);

    //	home = getenv("HOME");
    //	if (!home)
    //	  derror("Please set $HOME to your home directory");
    //	sprintf(basedefault, "%s/.doomrc", home);


    for (i=1 ; i<c ; i++)
    {
	if (!strcmp(v[i], "-quiet"))
	{
	    snd_verbose = 0;
	}
    }

    numsounds = NUMSFX;
    longsound = 0;

    if (! access(doom2fwad, R_OK) )
	name = doom2fwad;
    else if (! access(doom2wad, R_OK) )
	name = doom2wad;
    else if (! access(doomuwad, R_OK) )
	name = doomuwad;
    else if (! access(doomwad, R_OK) )
	name = doomwad;
    else if (! access(doom1wad, R_OK) )
	name = doom1wad;
    // else if (! access(DEVDATA "doom2.wad", R_OK) )
    //   name = DEVDATA "doom2.wad";
    //   else if (! access(DEVDATA "doom.wad", R_OK) )
    //   name = DEVDATA "doom.wad";
    else
    {
	fprintf(stderr, "Could not find wadfile anywhere\n");
	exit(-1);
    }

    
    openwad(name);
    if (snd_verbose)
	fprintf(stderr, "loading from [%s]\n", name);

    for (i=1 ; i<NUMSFX ; i++)
    {
	if (!S_sfx[i].link)
	{
	    S_sfx[i].data = getsfx(S_sfx[i].name, &lengths[i]);
	    if (longsound < lengths[i]) longsound = lengths[i];
	} else {
	    S_sfx[i].data = S_sfx[i].link->data;
	    lengths[i] = lengths[(S_sfx[i].link - S_sfx)/sizeof(sfxinfo_t)];
	}
	// test only
	//  {
	//  int fd;
	//  char name[10];
	//  sprintf(name, "sfx%d", i);
	//  fd = open(name, O_WRONLY|O_CREAT, 0644);
	//  write(fd, S_sfx[i].data, lengths[i]);
	//  close(fd);
	//  }
    }

}