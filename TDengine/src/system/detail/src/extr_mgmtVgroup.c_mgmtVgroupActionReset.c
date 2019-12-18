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
struct TYPE_3__ {char* updateEnd; } ;
typedef  TYPE_1__ SVgObj ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,char*,int) ; 

void *mgmtVgroupActionReset(void *row, char *str, int size, int *ssize) {
  SVgObj *pVgroup = (SVgObj *)row;
  int     tsize = pVgroup->updateEnd - (char *)pVgroup;

  memcpy(pVgroup, str, tsize);

  return NULL;
}