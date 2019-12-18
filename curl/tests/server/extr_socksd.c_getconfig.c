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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {void* connectrep; void* responsemethod; void* password; void* user; void* port; void* addr; void* nmethods_max; void* nmethods_min; void* version; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_READTEXT ; 
 void* byteval (char*) ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  configfile ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  resetdefaults () ; 
 void* shortval (char*) ; 
 int sscanf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (void*,char*) ; 

__attribute__((used)) static void getconfig(void)
{
  FILE *fp = fopen(configfile, FOPEN_READTEXT);
  resetdefaults();
  if(fp) {
    char buffer[512];
    logmsg("parse config file");
    while(fgets(buffer, sizeof(buffer), fp)) {
      char key[32];
      char value[32];
      if(2 == sscanf(buffer, "%31s %31s", key, value)) {
        if(!strcmp(key, "version")) {
          config.version = byteval(value);
          logmsg("version [%d] set", config.version);
        }
        else if(!strcmp(key, "nmethods_min")) {
          config.nmethods_min = byteval(value);
          logmsg("nmethods_min [%d] set", config.nmethods_min);
        }
        else if(!strcmp(key, "nmethods_max")) {
          config.nmethods_max = byteval(value);
          logmsg("nmethods_max [%d] set", config.nmethods_max);
        }
        else if(!strcmp(key, "backend")) {
          strcpy(config.addr, value);
          logmsg("backend [%s] set", config.addr);
        }
        else if(!strcmp(key, "backendport")) {
          config.port = shortval(value);
          logmsg("backendport [%d] set", config.port);
        }
        else if(!strcmp(key, "user")) {
          strcpy(config.user, value);
          logmsg("user [%s] set", config.user);
        }
        else if(!strcmp(key, "password")) {
          strcpy(config.password, value);
          logmsg("password [%s] set", config.password);
        }
        /* Methods:
           o  X'00' NO AUTHENTICATION REQUIRED
           o  X'01' GSSAPI
           o  X'02' USERNAME/PASSWORD
        */
        else if(!strcmp(key, "method")) {
          config.responsemethod = byteval(value);
          logmsg("method [%d] set", config.responsemethod);
        }
        else if(!strcmp(key, "response")) {
          config.connectrep = byteval(value);
          logmsg("response [%d] set", config.connectrep);
        }
      }
    }
    fclose(fp);
  }
}