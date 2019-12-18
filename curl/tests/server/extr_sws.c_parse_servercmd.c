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
struct httprequest {char* testno; int skip; int writedelay; void* close; void* upgrade; void* connmon; int /*<<< orphan*/  rcmd; void* open; void* auth_req; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_AUTH_REQUIRED ; 
 int /*<<< orphan*/  CMD_CONNECTIONMONITOR ; 
 int /*<<< orphan*/  CMD_IDLE ; 
 int /*<<< orphan*/  CMD_STREAM ; 
 int /*<<< orphan*/  CMD_SWSCLOSE ; 
 int /*<<< orphan*/  CMD_UPGRADE ; 
 void* FALSE ; 
 int /*<<< orphan*/  RCMD_IDLE ; 
 int /*<<< orphan*/  RCMD_STREAM ; 
 void* TRUE ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getpart (char**,size_t*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int sscanf (char*,char*,int*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* test2file (char*) ; 

__attribute__((used)) static int parse_servercmd(struct httprequest *req)
{
  FILE *stream;
  char *filename;
  int error;

  filename = test2file(req->testno);
  req->close = FALSE;
  stream = fopen(filename, "rb");
  if(!stream) {
    error = errno;
    logmsg("fopen() failed with error: %d %s", error, strerror(error));
    logmsg("  [1] Error opening file: %s", filename);
    logmsg("  Couldn't open test file %ld", req->testno);
    req->open = FALSE; /* closes connection */
    return 1; /* done */
  }
  else {
    char *orgcmd = NULL;
    char *cmd = NULL;
    size_t cmdsize = 0;
    int num = 0;

    /* get the custom server control "commands" */
    error = getpart(&orgcmd, &cmdsize, "reply", "servercmd", stream);
    fclose(stream);
    if(error) {
      logmsg("getpart() failed with error: %d", error);
      req->open = FALSE; /* closes connection */
      return 1; /* done */
    }

    req->connmon = FALSE;

    cmd = orgcmd;
    while(cmd && cmdsize) {
      char *check;

      if(!strncmp(CMD_AUTH_REQUIRED, cmd, strlen(CMD_AUTH_REQUIRED))) {
        logmsg("instructed to require authorization header");
        req->auth_req = TRUE;
      }
      else if(!strncmp(CMD_IDLE, cmd, strlen(CMD_IDLE))) {
        logmsg("instructed to idle");
        req->rcmd = RCMD_IDLE;
        req->open = TRUE;
      }
      else if(!strncmp(CMD_STREAM, cmd, strlen(CMD_STREAM))) {
        logmsg("instructed to stream");
        req->rcmd = RCMD_STREAM;
      }
      else if(!strncmp(CMD_CONNECTIONMONITOR, cmd,
                       strlen(CMD_CONNECTIONMONITOR))) {
        logmsg("enabled connection monitoring");
        req->connmon = TRUE;
      }
      else if(!strncmp(CMD_UPGRADE, cmd, strlen(CMD_UPGRADE))) {
        logmsg("enabled upgrade to http2");
        req->upgrade = TRUE;
      }
      else if(!strncmp(CMD_SWSCLOSE, cmd, strlen(CMD_SWSCLOSE))) {
        logmsg("swsclose: close this connection after response");
        req->close = TRUE;
      }
      else if(1 == sscanf(cmd, "skip: %d", &num)) {
        logmsg("instructed to skip this number of bytes %d", num);
        req->skip = num;
      }
      else if(1 == sscanf(cmd, "writedelay: %d", &num)) {
        logmsg("instructed to delay %d secs between packets", num);
        req->writedelay = num;
      }
      else {
        logmsg("Unknown <servercmd> instruction found: %s", cmd);
      }
      /* try to deal with CRLF or just LF */
      check = strchr(cmd, '\r');
      if(!check)
        check = strchr(cmd, '\n');

      if(check) {
        /* get to the letter following the newline */
        while((*check == '\r') || (*check == '\n'))
          check++;

        if(!*check)
          /* if we reached a zero, get out */
          break;
        cmd = check;
      }
      else
        break;
    }
    free(orgcmd);
  }

  return 0; /* OK! */
}