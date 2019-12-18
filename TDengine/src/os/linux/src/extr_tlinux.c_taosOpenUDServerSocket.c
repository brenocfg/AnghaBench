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
struct sockaddr_un {scalar_t__ sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  serverAdd ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  pError (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pTrace (char*,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,short) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tclose (int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int taosOpenUDServerSocket(char *ip, short port) {
  struct sockaddr_un serverAdd;
  int                sockFd;
  char               name[128];

  pTrace("open ud socket:%s", name);
  // if (tsAllowLocalhost) ip = "0.0.0.0";
  sprintf(name, "%s.%d", ip, port);

  bzero((char *)&serverAdd, sizeof(serverAdd));
  serverAdd.sun_family = AF_UNIX;
  strcpy(serverAdd.sun_path + 1, name);
  unlink(name);

  if ((sockFd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    pError("failed to open UD socket:%s, reason:%s", name, strerror(errno));
    return -1;
  }

  /* bind socket to server address */
  if (bind(sockFd, (struct sockaddr *)&serverAdd, sizeof(serverAdd)) < 0) {
    pError("bind socket:%s failed, reason:%s", name, strerror(errno));
    tclose(sockFd);
    return -1;
  }

  if (listen(sockFd, 10) < 0) {
    pError("listen socket:%s failed, reason:%s", name, strerror(errno));
    return -1;
  }

  return sockFd;
}