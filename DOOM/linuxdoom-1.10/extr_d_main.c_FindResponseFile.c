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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXARGVS ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 int myargc ; 
 char** myargv ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void FindResponseFile (void)
{
    int             i;
#define MAXARGVS        100
	
    for (i = 1;i < myargc;i++)
	if (myargv[i][0] == '@')
	{
	    FILE *          handle;
	    int             size;
	    int             k;
	    int             index;
	    int             indexinfile;
	    char    *infile;
	    char    *file;
	    char    *moreargs[20];
	    char    *firstargv;
			
	    // READ THE RESPONSE FILE INTO MEMORY
	    handle = fopen (&myargv[i][1],"rb");
	    if (!handle)
	    {
		printf ("\nNo such response file!");
		exit(1);
	    }
	    printf("Found response file %s!\n",&myargv[i][1]);
	    fseek (handle,0,SEEK_END);
	    size = ftell(handle);
	    fseek (handle,0,SEEK_SET);
	    file = malloc (size);
	    fread (file,size,1,handle);
	    fclose (handle);
			
	    // KEEP ALL CMDLINE ARGS FOLLOWING @RESPONSEFILE ARG
	    for (index = 0,k = i+1; k < myargc; k++)
		moreargs[index++] = myargv[k];
			
	    firstargv = myargv[0];
	    myargv = malloc(sizeof(char *)*MAXARGVS);
	    memset(myargv,0,sizeof(char *)*MAXARGVS);
	    myargv[0] = firstargv;
			
	    infile = file;
	    indexinfile = k = 0;
	    indexinfile++;  // SKIP PAST ARGV[0] (KEEP IT)
	    do
	    {
		myargv[indexinfile++] = infile+k;
		while(k < size &&
		      ((*(infile+k)>= ' '+1) && (*(infile+k)<='z')))
		    k++;
		*(infile+k) = 0;
		while(k < size &&
		      ((*(infile+k)<= ' ') || (*(infile+k)>'z')))
		    k++;
	    } while(k < size);
			
	    for (k = 0;k < index;k++)
		myargv[indexinfile++] = moreargs[k];
	    myargc = indexinfile;
	
	    // DISPLAY ARGS
	    printf("%d command-line args:\n",myargc);
	    for (k=1;k<myargc;k++)
		printf("%s\n",myargv[k]);

	    break;
	}
}