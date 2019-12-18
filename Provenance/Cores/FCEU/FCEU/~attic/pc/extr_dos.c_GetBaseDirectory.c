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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 scalar_t__* BaseDirectory ; 
 char* arg0 ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,char*,int) ; 

uint8 *GetBaseDirectory(void)
{
 int x=0;
 uint8 *ret = 0;

 if(arg0)
  for(x=strlen(arg0);x>=0;x--)
  {
   if(arg0[x]=='/' || arg0[x]=='\\')
   {
    ret = malloc(x + 1);
    strncpy(ret,arg0,x);
    break;
   }
  }

 if(!ret) { x=0; ret = malloc(1); }

 BaseDirectory[x]=0;
}