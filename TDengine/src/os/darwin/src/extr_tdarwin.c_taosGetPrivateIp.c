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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct ifaddrs {TYPE_1__* ifa_addr; int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; } ;
struct TYPE_2__ {int sa_family; } ;

/* Variables and functions */
 int AF_INET ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 int getifaddrs (struct ifaddrs**) ; 
 int getnameinfo (TYPE_1__*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pPrint (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char* const,char*) ; 

int taosGetPrivateIp(char *const ip) {
  bool hasLoCard = false;

  struct ifaddrs *ifaddr, *ifa;
  int             family, s;
  char            host[NI_MAXHOST];

  if (getifaddrs(&ifaddr) == -1) {
    return -1;
  }

  /* Walk through linked list, maintaining head pointer so we can free list later */
  int flag = 0;
  for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == NULL) continue;

    family = ifa->ifa_addr->sa_family;
    if (strcmp("lo", ifa->ifa_name) == 0) {
      hasLoCard = true;
      continue;
    }

    if (family == AF_INET) {
      /* printf("%-8s", ifa->ifa_name); */
      s = getnameinfo(ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
                      host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
      if (s != 0) {
        freeifaddrs(ifaddr);
        return -1;
      }

      strcpy(ip, host);
      flag = 1;
      break;
    }
  }

  freeifaddrs(ifaddr);
  if (flag) {
    return 0;
  } else {
    if (hasLoCard) {
      pPrint("no net card was found, use lo:127.0.0.1 as default");
      strcpy(ip, "127.0.0.1");
      return 0;
    }
    return -1;
  }
}