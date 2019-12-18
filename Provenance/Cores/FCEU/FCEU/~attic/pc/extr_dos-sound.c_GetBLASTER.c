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
 int SBDMA ; 
 int SBDMA16 ; 
 int SBIRQ ; 
 int SBPort ; 
 scalar_t__ format ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int sscanf (char*,char*,int*) ; 
 int toupper (char) ; 

int GetBLASTER(void)
{
 int check=0;
 char *s;

 if(!(s=getenv("BLASTER")))
 {
  puts(" Error getting BLASTER environment variable.");
  return(0);
 }

 while(*s)
 {
  switch(toupper(*s))
  {
   case 'A': check|=(sscanf(s+1,"%x",&SBPort)==1)?1:0;break;
   case 'I': check|=(sscanf(s+1,"%d",&SBIRQ)==1)?2:0;break;
   case 'D': check|=(sscanf(s+1,"%d",&SBDMA)==1)?4:0;break;
   case 'H': check|=(sscanf(s+1,"%d",&SBDMA16)==1)?8:0;break;
  }
  s++;
 }
 
 if((check^7)&7 || SBDMA>=4 || (SBDMA16<=4 && check&8) || SBIRQ>15)
 {
  puts(" Invalid or incomplete BLASTER environment variable.");
  return(0);
 }
 if(!(check&8))
  format=0;
 return(1);
}