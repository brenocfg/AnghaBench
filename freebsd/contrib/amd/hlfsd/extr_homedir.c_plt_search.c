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
struct TYPE_4__ {scalar_t__ uid; } ;
typedef  TYPE_1__ uid2home_t ;
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int cur_pwtab_num ; 
 TYPE_1__* pwtab ; 

uid2home_t *
plt_search(u_int u)
{
  int max, min, mid;

  /*
   * empty table should not happen,
   * but I have a bug with signals to trace...
   */
  if (pwtab == (uid2home_t *) NULL)
    return (uid2home_t *) NULL;

  max = cur_pwtab_num - 1;
  min = 0;

  do {
    mid = (max + min) / 2;
    if (pwtab[mid].uid == u)	/* record found! */
      return &pwtab[mid];
    if (pwtab[mid].uid > u)
      max = mid;
    else
      min = mid;
  } while (max > min + 1);

  if (pwtab[max].uid == u)
    return &pwtab[max];
  if (pwtab[min].uid == u)
    return &pwtab[min];

  /* if gets here then record was not found */
  return (uid2home_t *) NULL;
}