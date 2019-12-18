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
typedef  int UCHAR ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int* kstrstr (int*,...) ; 
 scalar_t__ memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcat (int*,...) ; 
 int /*<<< orphan*/  strcpy (int*,int*) ; 
 int strlen (int*) ; 

__attribute__((used)) static int Config_FileGetParameter(UCHAR *string, UCHAR *dest,UCHAR *source)
{
  UCHAR buf1[100];
  UCHAR buf2[100];
  UCHAR *start_p=NULL,*end_p=NULL,*tmp_p=NULL;
  int ii;

    memset(buf1,0,100);
    strcat(buf1, string);
    strcat(buf1, "=");
    source+=strlen(buf1);

//find target string start point
    if((start_p = kstrstr(source,buf1))==NULL)
	return FALSE;

//check if current config line is marked by "#" ??
for(ii=1;;ii++) {
  if(memcmp(start_p-ii,"\n",1)==0)
      break;
  if(memcmp(start_p-ii,"#",1)==0)
      return FALSE;
}

//find target string end point
     if((end_p = kstrstr(start_p,"\n"))==NULL) {       //cann't find "\n",but don't care
          end_p=start_p+strlen(start_p);   //no include "\n"
       }

   memset(buf2,0,100);
   memcpy(buf2,start_p,end_p-start_p);    //get the tartget line
   buf2[end_p-start_p]='\0';

   //find value
   if((start_p = kstrstr(buf2,"="))==NULL)
      return FALSE;
   memset(buf1,0,100);
   strcpy(buf1,start_p+1);

  //except space
  tmp_p = buf1;
  while(*tmp_p != 0x00) {
  	if(*tmp_p==' ')
	    tmp_p++;
         else
	  break;
  }

   memcpy(dest,tmp_p,strlen(tmp_p));
 return TRUE;
}