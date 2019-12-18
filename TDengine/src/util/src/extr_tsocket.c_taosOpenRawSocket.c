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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  rawAdd ;
typedef  int /*<<< orphan*/  hold ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IP_HDRINCL ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  pError (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pTrace (char*,char*) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ taosSetSockOpt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

int taosOpenRawSocket(char *ip) {
  int                fd, hold;
  struct sockaddr_in rawAdd;

  pTrace("open udp raw socket:%s", ip);
  // if (tsAllowLocalhost) ip = "0.0.0.0";

  fd = (int)socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
  if (fd < 0) {
    pError("failed to open raw socket: %d (%s)", errno, strerror(errno));
    return -1;
  }

  hold = 1;
  if (taosSetSockOpt(fd, IPPROTO_IP, IP_HDRINCL, (void *)&hold, sizeof(hold)) < 0) {
    pError("failed to set hold option: %d (%s)", errno, strerror(errno));
    close(fd);
    return -1;
  }

  bzero((char *)&rawAdd, sizeof(rawAdd));
  rawAdd.sin_family = AF_INET;
  rawAdd.sin_addr.s_addr = inet_addr(ip);

  if (bind(fd, (struct sockaddr *)&rawAdd, sizeof(rawAdd)) < 0) {
    pError("failed to bind RAW socket: %d (%s)", errno, strerror(errno));
    close(fd);
    return -1;
  }

  return fd;
}