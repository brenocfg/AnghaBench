#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_6__ {int cpuid; int len; } ;
struct TYPE_7__ {unsigned int* regs; TYPE_1__ header; } ;
typedef  TYPE_2__ packet_t ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CANONNAME ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int accept (int,struct sockaddr*,int*) ; 
 int atoi (char*) ; 
 int bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int recv (int,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 char** regnames ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tmp_size ; 

int main(int argc, char *argv[])
{
  unsigned int pc_trace[5][4], pc_trace_p[5] = { 0, };
  struct addrinfo *ai, *ais, hints;
  int sock = -1, sock1, sock2;
  struct sockaddr_in6 sa;
  packet_t packet1, packet2;
  int i, ret, cnt, cpuid;
  int check_len_override = 0;
  socklen_t sal;

  if (argv[1] != NULL)
    check_len_override = atoi(argv[1]);

  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = AI_CANONNAME;
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  ret = getaddrinfo("::", "1234", &hints, &ais);
  if (ret != 0)
    return -1;

  for (ai = ais; ai != NULL; ai = ai->ai_next) {
    sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (sock == -1)
      continue;

    ret = bind(sock, ai->ai_addr, ai->ai_addrlen);
    if (ret != 0) {
      close(sock);
      sock = -1;
      continue;
    }
    break;
  }
  freeaddrinfo(ais);

  if (sock == -1) {
    perror("failed to bind");
    return -1;
  }
 
  ret = listen(sock, SOMAXCONN);
  if (ret != 0) {
    perror("failed to listen");
    return -1;
  }

  sal = sizeof(sa);
  sock1 = accept(sock, (struct sockaddr *)&sa, &sal);
  if (sock1 == -1) {
    perror("failed to accept");
    return -1;
  }
  printf("client1 connected\n");

  sal = sizeof(sa);
  sock2 = accept(sock, (struct sockaddr *)&sa, &sal);
  if (sock2 == -1) {
    perror("failed to accept");
    return -1;
  }
  printf("client2 connected\n");

  for (cnt = 0; ; cnt++)
  {
    int len;
#define tmp_size (4+4 + 24*4 + 2*4)
    ret = recv(sock1, &packet1, tmp_size, MSG_WAITALL);
    if (ret != tmp_size) {
      if (ret < 0)
        perror("recv1");
      else
        printf("recv1 %d\n", ret);
      return -1;
    }
    ret = recv(sock2, &packet2, tmp_size, MSG_WAITALL);
    if (ret != tmp_size) {
      if (ret < 0)
        perror("recv2");
      else
        printf("recv2 %d\n", ret);
      return -1;
    }

    cpuid = packet1.header.cpuid;
    len = sizeof(packet1.header) + packet1.header.len;
    if (check_len_override > 0)
      len = check_len_override;

    if (memcmp(&packet1, &packet2, len) == 0) {
      pc_trace[cpuid][pc_trace_p[cpuid]++ & 3] = packet1.regs[0];
      continue;
    }

    if (packet1.header.cpuid != packet2.header.cpuid)
      printf("%d: CPU %d %d\n", cnt, packet1.header.cpuid & 0xff, packet2.header.cpuid & 0xff);
    else if (*(int *)&packet1.header != *(int *)&packet2.header)
      printf("%d: header\n", cnt);

    // check regs (and stuff)
    for (i = 0; i < 1+24+2; i++)
      if (packet1.regs[i] != packet2.regs[i])
        printf("%d: %3s: %08x %08x\n", cnt, regnames[i], packet1.regs[i], packet2.regs[i]);

    break;
  }

  printf("--\nCPU %d\n", cpuid);
  for (cpuid = 0; cpuid < 2; cpuid++) {
    printf("trace%d: ", cpuid);
    for (i = 0; i < 4; i++)
      printf(" %08x", pc_trace[cpuid][pc_trace_p[cpuid]++ & 3]);

    if (packet1.header.cpuid == cpuid)
      printf(" %08x", packet1.regs[0]);
    else if (packet2.header.cpuid == cpuid)
      printf(" %08x", packet2.regs[0]);
    printf("\n");
  }

  for (i = 0; i < 24+1; i++)
    printf("%3s: %08x %08x\n", regnames[i], packet1.regs[i], packet2.regs[i]);

  return 0;
}