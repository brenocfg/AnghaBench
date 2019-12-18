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
typedef  int /*<<< orphan*/  serverAddr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pError (char*,char*,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,short) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int taosOpenUDClientSocket(char *ip, short port) {
  int                sockFd = 0;
  struct sockaddr_un serverAddr;
  int                ret;
  char               name[128];
  sprintf(name, "%s.%d", ip, port);

  sockFd = socket(AF_UNIX, SOCK_STREAM, 0);

  if (sockFd < 0) {
    pError("failed to open the UD socket:%s, reason:%s", name, strerror(errno));
    return -1;
  }

  memset((char *)&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sun_family = AF_UNIX;
  strcpy(serverAddr.sun_path + 1, name);

  ret = connect(sockFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  if (ret != 0) {
    pError("failed to connect UD socket, name:%d, reason: %s", name, strerror(errno));
    sockFd = -1;
  }

  return sockFd;
}