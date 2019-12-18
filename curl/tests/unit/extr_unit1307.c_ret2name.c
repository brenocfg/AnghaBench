#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static const char *ret2name(int i)
{
  switch(i) {
  case 0:
    return "MATCH";
  case 1:
    return "NOMATCH";
  case 2:
    return "FAIL";
  default:
    return "unknown";
  }
  /* not reached */
}