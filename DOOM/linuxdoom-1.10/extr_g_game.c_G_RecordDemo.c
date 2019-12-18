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

/* Variables and functions */
 int M_CheckParm (char*) ; 
 int /*<<< orphan*/  PU_STATIC ; 
 scalar_t__ Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ demobuffer ; 
 scalar_t__ demoend ; 
 int /*<<< orphan*/  demoname ; 
 int demorecording ; 
 int myargc ; 
 int /*<<< orphan*/ * myargv ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int usergame ; 

void G_RecordDemo (char* name) 
{ 
    int             i; 
    int				maxsize;
	
    usergame = false; 
    strcpy (demoname, name); 
    strcat (demoname, ".lmp"); 
    maxsize = 0x20000;
    i = M_CheckParm ("-maxdemo");
    if (i && i<myargc-1)
	maxsize = atoi(myargv[i+1])*1024;
    demobuffer = Z_Malloc (maxsize,PU_STATIC,NULL); 
    demoend = demobuffer + maxsize;
	
    demorecording = true; 
}