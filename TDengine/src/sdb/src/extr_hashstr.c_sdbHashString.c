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
struct TYPE_2__ {unsigned int maxSessions; } ;
typedef  TYPE_1__ SHashObj ;

/* Variables and functions */
 int strlen (char*) ; 

int sdbHashString(void *handle, char *string) {
  SHashObj *   pObj = (SHashObj *)handle;
  unsigned int hash = 0, hashv;
  char *       c;
  int          len = strlen(string);

  c = string;

  while (len >= 4) {
    hash += *((int *)c);
    c += 4;
    len -= 4;
  }

  while (len > 0) {
    hash += *c;
    c++;
    len--;
  }

  hashv = hash / pObj->maxSessions;
  hash = (hashv + hash % pObj->maxSessions) % pObj->maxSessions;

  return hash;
}