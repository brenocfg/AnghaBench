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
struct TYPE_2__ {int /*<<< orphan*/  username; } ;

/* Variables and functions */
 scalar_t__ STREQ (int /*<<< orphan*/ ,char*) ; 
 int cur_pwtab_num ; 
 int strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* untab ; 

int
untab_index(char *username)
{
  int max, min, mid, cmp;

  max = cur_pwtab_num - 1;
  min = 0;

  do {
    mid = (max + min) / 2;
    cmp = strcmp(untab[mid].username, username);
    if (cmp == 0)		/* record found! */
      return mid;
    if (cmp > 0)
      max = mid;
    else
      min = mid;
  } while (max > min + 1);

  if (STREQ(untab[max].username, username))
    return max;
  if (STREQ(untab[min].username, username))
    return min;

  /* if gets here then record was not found */
  return -1;
}