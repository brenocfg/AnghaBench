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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; TYPE_1__ sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  serverAddr ;
typedef  int /*<<< orphan*/  clientAddr ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ htons (scalar_t__) ; 
 void* inet_addr (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pError (char*,char*,...) ; 
 int /*<<< orphan*/  pTrace (char*,char*,short) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taosCloseSocket (int) ; 

int taosOpenTcpClientSocket(char *destIp, short destPort, char *clientIp) {
  int                sockFd = 0;
  struct sockaddr_in serverAddr, clientAddr;
  int                ret;

  pTrace("open tcp client socket:%s:%d", destIp, destPort);
  // if (tsAllowLocalhost) destIp = "0.0.0.0";

  sockFd = (int)socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (sockFd < 0) {
    pError("failed to open the socket: %d (%s)", errno, strerror(errno));
    return -1;
  }

  if (clientIp && clientIp[0] && clientIp[0] != '0') {
    memset((char *)&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr(clientIp);
    clientAddr.sin_port = 0;

    /* bind socket to client address */
    if (bind(sockFd, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) < 0) {
      pError("bind tcp client socket failed, client(%s:0), dest(%s:%d), reason:%d(%s)",
             clientIp, destIp, destPort, errno, strerror(errno));
      close(sockFd);
      return -1;
    }
  }

  memset((char *)&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(destIp);
  serverAddr.sin_port = (uint16_t)htons((uint16_t)destPort);

  ret = connect(sockFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  if (ret != 0) {
    pError("failed to connect socket, ip:%s, port:%d, reason: %s", destIp, destPort, strerror(errno));
    taosCloseSocket(sockFd);
    sockFd = -1;
  }

  return sockFd;
}