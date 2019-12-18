#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s ;
struct TYPE_3__ {int /*<<< orphan*/  ip_net_num; int /*<<< orphan*/  ip_net_name; struct TYPE_3__* ip_next; } ;
typedef  TYPE_1__ addrlist ;

/* Variables and functions */
 char* SALLOC (int) ; 
 TYPE_1__* localnets ; 
 scalar_t__ strlen (char*) ; 
 char* xrealloc (char*,int) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  xstrlcat (char*,char*,int) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,int) ; 

char *
print_wires(void)
{
  addrlist *al;
  char s[256];
  int i;
  char *buf;
  int bufcount = 0;
  int buf_size = 1024;

  buf = SALLOC(buf_size);	/* initial allocation (may grow!) */
  if (!buf)
    return NULL;

  if (!localnets) {
    xstrlcpy(buf, "No networks\n", buf_size);
    return buf;
  }
  /* check if there's more than one network */
  if (!localnets->ip_next) {
    /* use buf_size for sizeof(buf) because of the realloc() below */
    xsnprintf(buf, buf_size,
	      "Network: wire=\"%s\" (netnumber=%s).\n",
	      localnets->ip_net_name, localnets->ip_net_num);
    return buf;
  }
  buf[0] = '\0';		/* null out buffer before appending */
  for (i = 1, al = localnets; al; al = al->ip_next, i++) {
    xsnprintf(s, sizeof(s), "Network %d: wire=\"%s\" (netnumber=%s).\n",
	      i, al->ip_net_name, al->ip_net_num);
    bufcount += strlen(s);
    if (bufcount > buf_size) {
      buf_size *= 2;
      buf = xrealloc(buf, buf_size);
    }
    xstrlcat(buf, s, buf_size);
  }
  return buf;
}