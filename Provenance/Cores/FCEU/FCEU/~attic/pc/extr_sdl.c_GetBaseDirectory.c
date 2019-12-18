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
typedef  char uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleFileName (int /*<<< orphan*/ *,char*,int) ; 
 int MAX_PATH ; 
 char* getenv (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

uint8 *GetBaseDirectory(void)
{
 uint8 *ol;
 uint8 *ret; 

 ol=getenv("HOME");

 if(ol)
 {
  ret=malloc(strlen(ol)+1+strlen("./fceultra"));
  strcpy(ret,ol);
  strcat(ret,"/.fceultra");
 }
 else
 {
  #ifdef WIN32
  char *sa;

  ret=malloc(MAX_PATH+1);
  GetModuleFileName(NULL,ret,MAX_PATH+1);

  sa=strrchr(ret,'\\');
  if(sa)
   *sa = 0; 
  #else
  ret=malloc(1);
  ret[0]=0;
  #endif
  printf("%s\n",ret);
 }
 return(ret);
}