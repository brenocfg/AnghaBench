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
struct timeval {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  I_InitMusic () ; 
 int /*<<< orphan*/  I_InitSound (int,int) ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 TYPE_1__* S_sfx ; 
 int addsfx (int,int,int,int) ; 
 int /*<<< orphan*/ * channels ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fdset ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  grabdata (int,char**) ; 
 int /*<<< orphan*/  initdata () ; 
 int /*<<< orphan*/ * lengths ; 
 int /*<<< orphan*/  mytime ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  quit () ; 
 int read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  scratchset ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 
 scalar_t__ snd_verbose ; 
 int /*<<< orphan*/  stderr ; 
 int* steptable ; 
 int /*<<< orphan*/  updatesounds () ; 
 int /*<<< orphan*/  write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main
( int		c,
  char**	v )
{

    int		done = 0;
    int		rc;
    int		nrc;
    int		sndnum;
    int		handle = 0;
    
    unsigned char	commandbuf[10];
    struct timeval	zerowait = { 0, 0 };

    
    int 	step;
    int 	vol;
    int		sep;
    
    int		i;
    int		waitingtofinish=0;

    // get sound data
    grabdata(c, v);

    // init any data
    initdata();		

    I_InitSound(11025, 16);

    I_InitMusic();

    if (snd_verbose)
	fprintf(stderr, "ready\n");
    
    // parse commands and play sounds until done
    FD_ZERO(&fdset);
    FD_SET(0, &fdset);

    while (!done)
    {
	mytime++;

	if (!waitingtofinish)
	{
	    do {
		scratchset = fdset;
		rc = select(FD_SETSIZE, &scratchset, 0, 0, &zerowait);

		if (rc > 0)
		{
		    //	fprintf(stderr, "select is true\n");
		    // got a command
		    nrc = read(0, commandbuf, 1);

		    if (!nrc)
		    {
			done = 1;
			rc = 0;
		    }
		    else
		    {
			if (snd_verbose)
			    fprintf(stderr, "cmd: %c", commandbuf[0]);

			switch (commandbuf[0])
			{
			  case 'p':
			    // play a new sound effect
			    read(0, commandbuf, 9);

			    if (snd_verbose)
			    {
				commandbuf[9]=0;
				fprintf(stderr, "%s\n", commandbuf);
			    }

			    commandbuf[0] -=
				commandbuf[0]>='a' ? 'a'-10 : '0';
			    commandbuf[1] -=
				commandbuf[1]>='a' ? 'a'-10 : '0';
			    commandbuf[2] -=
				commandbuf[2]>='a' ? 'a'-10 : '0';
			    commandbuf[3] -=
				commandbuf[3]>='a' ? 'a'-10 : '0';
			    commandbuf[4] -=
				commandbuf[4]>='a' ? 'a'-10 : '0';
			    commandbuf[5] -=
				commandbuf[5]>='a' ? 'a'-10 : '0';
			    commandbuf[6] -=
				commandbuf[6]>='a' ? 'a'-10 : '0';
			    commandbuf[7] -=
				commandbuf[7]>='a' ? 'a'-10 : '0';

			    //	p<snd#><step><vol><sep>
			    sndnum = (commandbuf[0]<<4) + commandbuf[1];
			    step = (commandbuf[2]<<4) + commandbuf[3];
			    step = steptable[step];
			    vol = (commandbuf[4]<<4) + commandbuf[5];
			    sep = (commandbuf[6]<<4) + commandbuf[7];

			    handle = addsfx(sndnum, vol, step, sep);
			    // returns the handle
			    //	outputushort(handle);
			    break;
			    
			  case 'q':
			    read(0, commandbuf, 1);
			    waitingtofinish = 1; rc = 0;
			    break;
			    
			  case 's':
			  {
			      int fd;
			      read(0, commandbuf, 3);
			      commandbuf[2] = 0;
			      fd = open((char*)commandbuf, O_CREAT|O_WRONLY, 0644);
			      commandbuf[0] -= commandbuf[0]>='a' ? 'a'-10 : '0';
			      commandbuf[1] -= commandbuf[1]>='a' ? 'a'-10 : '0';
			      sndnum = (commandbuf[0]<<4) + commandbuf[1];
			      write(fd, S_sfx[sndnum].data, lengths[sndnum]);
			      close(fd);
			  }
			  break;
			  
			  default:
			    fprintf(stderr, "Did not recognize command\n");
			    break;
			}
		    }
		}
		else if (rc < 0)
		{
		    quit();
		}
	    } while (rc > 0);
	}

	updatesounds();

	if (waitingtofinish)
	{
	    for(i=0 ; i<8 && !channels[i] ; i++);
	    
	    if (i==8)
		done=1;
	}

    }

    quit();
    return 0;
}