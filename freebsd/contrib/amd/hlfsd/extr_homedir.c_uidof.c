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
struct TYPE_2__ {int uid; } ;

/* Variables and functions */
 int INVALIDID ; 
 TYPE_1__* untab ; 
 int untab_index (char*) ; 

int
uidof(char *username)
{
  int idx;

  if ((idx = untab_index(username)) < 0)	/* not found */
    return INVALIDID;			/* an invalid user id */
  return untab[idx].uid;
}