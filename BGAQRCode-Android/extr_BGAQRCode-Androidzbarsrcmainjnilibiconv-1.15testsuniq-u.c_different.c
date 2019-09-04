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
 int memcmp (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (size_t,size_t) ; 

__attribute__((used)) static int
different (const char *old, const char *new, size_t oldlen, size_t newlen)
{
  int order;

  order = memcmp (old, new, min (oldlen, newlen));

  if (order == 0)
    return oldlen - newlen;
  return order;
}