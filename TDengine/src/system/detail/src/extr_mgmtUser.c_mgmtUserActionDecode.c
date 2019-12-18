#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* updateEnd; } ;
typedef  TYPE_1__ SUserObj ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void *mgmtUserActionDecode(void *row, char *str, int size, int *ssize) {
  SUserObj *pUser = (SUserObj *)malloc(sizeof(SUserObj));
  if (pUser == NULL) return NULL;
  memset(pUser, 0, sizeof(SUserObj));

  int tsize = pUser->updateEnd - (char *)pUser;
  memcpy(pUser, str, tsize);
  return (void *)pUser;
}