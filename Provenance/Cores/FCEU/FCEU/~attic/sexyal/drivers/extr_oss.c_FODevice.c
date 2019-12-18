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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 scalar_t__ IDBASE ; 
 int O_NONBLOCK ; 
 int O_WRONLY ; 
 scalar_t__ SEXYAL_ID_DEFAULT ; 
 scalar_t__ SEXYAL_ID_UNUSED ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  sal_strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sal_strcpy (char*,char*) ; 
 int /*<<< orphan*/  sal_uinttos (scalar_t__) ; 

__attribute__((used)) static int FODevice(uint64_t id)
{
 char fn[64];

 if(id==SEXYAL_ID_DEFAULT)
 {
  sal_strcpy(fn,"/dev/dsp");
  return(open(fn,O_WRONLY));
 }
 else if(id==SEXYAL_ID_UNUSED)
 {
  int x=-1;
  int dspfd;
  do 
  {
   sal_strcpy(fn,"/dev/dsp");
   if(x!=-1)
    sal_strcat(fn,sal_uinttos(x));
   dspfd=open(fn,O_WRONLY|O_NONBLOCK);
   if(dspfd!=-1) break;
   x++;   
  } while(errno!=ENOENT);
  if(dspfd==-1) return(0);
  fcntl(dspfd,F_SETFL,fcntl(dspfd,F_GETFL)&~O_NONBLOCK);
  return(dspfd);
 }
 else
 {
  sal_strcpy(fn,"/dev/dsp");
  sal_strcat(fn,sal_uinttos(id-IDBASE));
  return(open(fn,O_WRONLY));
 }
}