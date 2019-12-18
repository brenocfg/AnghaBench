#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmpbuffer ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int ZoneType; int eAuthenMode; int eEncryptionStatus; } ;
struct TYPE_6__ {TYPE_1__ config_file; } ;
typedef  TYPE_2__* PSDevice ;

/* Variables and functions */
 scalar_t__ Config_FileGetParameter (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Config_FileOperation (TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 int ZoneType_Europe ; 
 int ZoneType_Japan ; 
 int ZoneType_USA ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ simple_strtol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int Read_config_file(PSDevice pDevice) {
  int result=0;
  UCHAR      tmpbuffer[100];
  UCHAR *buffer=NULL;

  //init config setting
 pDevice->config_file.ZoneType = -1;
 pDevice->config_file.eAuthenMode = -1;
 pDevice->config_file.eEncryptionStatus = -1;

  if((buffer=Config_FileOperation(pDevice)) ==NULL) {
     result =-1;
     return result;
  }

//get zonetype
{
    memset(tmpbuffer,0,sizeof(tmpbuffer));
    if(Config_FileGetParameter("ZONETYPE",tmpbuffer,buffer) ==TRUE) {
    if(memcmp(tmpbuffer,"USA",3)==0) {
      pDevice->config_file.ZoneType=ZoneType_USA;
    }
    else if(memcmp(tmpbuffer,"JAPAN",5)==0) {
      pDevice->config_file.ZoneType=ZoneType_Japan;
    }
    else if(memcmp(tmpbuffer,"EUROPE",6)==0) {
     pDevice->config_file.ZoneType=ZoneType_Europe;
    }
    else {
      printk("Unknown Zonetype[%s]?\n",tmpbuffer);
   }
 }
}

#if 1
//get other parameter
  {
	memset(tmpbuffer,0,sizeof(tmpbuffer));
       if(Config_FileGetParameter("AUTHENMODE",tmpbuffer,buffer)==TRUE) {
	 pDevice->config_file.eAuthenMode = (int) simple_strtol(tmpbuffer, NULL, 10);
       }

	memset(tmpbuffer,0,sizeof(tmpbuffer));
       if(Config_FileGetParameter("ENCRYPTIONMODE",tmpbuffer,buffer)==TRUE) {
	 pDevice->config_file.eEncryptionStatus= (int) simple_strtol(tmpbuffer, NULL, 10);
       }
  }
#endif

  kfree(buffer);
  return result;
}