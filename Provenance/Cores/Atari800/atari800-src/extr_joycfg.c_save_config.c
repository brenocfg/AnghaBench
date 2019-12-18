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
typedef  int /*<<< orphan*/  string ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 char** joyparams ; 
 size_t* joytypes ; 
 int** keysets ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rename (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void save_config()
{
  FILE *fr;
  FILE *fw;
  char string[256];
  int i;

  if ((fr=fopen("atari800.cfg","r"))==NULL)
  {
    printf("Error opening atari800.cfg!\n");
    return;
  }
  if ((fw=fopen("atari800.tmp","w"))==NULL)
  {
    printf("Error creating temporary file atari800.tmp!\n");
    fclose(fr);
    return;
  }
  while (fgets(string,sizeof(string),fr))
  {
    if (strncmp(string,"JOYSTICK_",9)!=0 && strncmp(string,"KEYSET_",7)!=0)
      fputs(string,fw);  /*copy all lines except those with JOYSTICK_ and KEYSET_ parameters*/
  }
  fclose(fr);
  i=strlen(string)-1;
  if (i>=0 && string[i]!='\n') fprintf(fw,"\n");
  for (i=0;i<4;i++)
    fprintf(fw,"KEYSET_%i=%i %i %i %i %i %i %i %i %i\n",i,
      keysets[i][0],keysets[i][1],keysets[i][2],keysets[i][3],
      keysets[i][4],keysets[i][5],keysets[i][6],keysets[i][7],
      keysets[i][8]);
  for (i=0;i<4;i++)
    fprintf(fw,"JOYSTICK_%i=%s\n",i,joyparams[joytypes[i]]);
  fclose(fw);
  if (rename("atari800.tmp","atari800.cfg")==0)
    printf("Configuration successfully saved.\n");
  else
    printf("Error when renaming atari800.tmp to atari800.cfg!\n");
}