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
struct TYPE_3__ {char const splitchar; struct TYPE_3__* eqkid; struct TYPE_3__* hikid; struct TYPE_3__* lokid; } ;
typedef  TYPE_1__ ternary_node ;
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */

__attribute__((used)) static PTR
ternary_recursivesearch (const ternary_node *p, const char *s)
{
  if (!p)
    return 0;
  if (*s < p->splitchar)
    return ternary_recursivesearch (p->lokid, s);
  else if (*s > p->splitchar)
    return ternary_recursivesearch (p->hikid, s);
  else
    {
      if (*s == 0)
	return (PTR) p->eqkid;
      return ternary_recursivesearch (p->eqkid, ++s);
    }
}