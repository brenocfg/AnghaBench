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
struct TYPE_3__ {scalar_t__ child; } ;
typedef  TYPE_1__ uid2home_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlog (char*,long,int) ; 
 scalar_t__ select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static void
delay(uid2home_t *found, int secs)
{
  struct timeval tv;

  if (found)
    dlog("delaying on child %ld for %d seconds", (long) found->child, secs);

  tv.tv_usec = 0;

  do {
    tv.tv_sec = secs;
    if (select(0, NULL, NULL, NULL, &tv) == 0)
      break;
  } while (--secs && found->child);
}