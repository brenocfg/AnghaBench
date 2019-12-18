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
struct hostent {scalar_t__ h_addrtype; scalar_t__ h_name; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int CFM_DOMAIN_STRIP ; 
 int CFM_NORMALIZE_HOSTNAMES ; 
 int /*<<< orphan*/  dlog (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  domain_strip (char*,int /*<<< orphan*/ ) ; 
 struct hostent* gethostbyname (char*) ; 
 TYPE_1__ gopt ; 
 int /*<<< orphan*/  hostd ; 
 char* strealloc (char*,char*) ; 

void
host_normalize(char **chp)
{
  /*
   * Normalize hosts is used to resolve host name aliases
   * and replace them with the standard-form name.
   * Invoked with "-n" command line option.
   */
  if (gopt.flags & CFM_NORMALIZE_HOSTNAMES) {
    struct hostent *hp;
    hp = gethostbyname(*chp);
    if (hp && hp->h_addrtype == AF_INET) {
      dlog("Hostname %s normalized to %s", *chp, hp->h_name);
      *chp = strealloc(*chp, (char *) hp->h_name);
    }
  }
  if (gopt.flags & CFM_DOMAIN_STRIP) {
    domain_strip(*chp, hostd);
  }
}