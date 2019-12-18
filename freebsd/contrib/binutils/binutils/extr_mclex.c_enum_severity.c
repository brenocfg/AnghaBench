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
struct TYPE_4__ {struct TYPE_4__ const* next; int /*<<< orphan*/  group_name; } ;
typedef  TYPE_1__ const mc_keyword ;

/* Variables and functions */
 TYPE_1__ const* keyword_top ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

const mc_keyword *
enum_severity (int e)
{
  mc_keyword *h = keyword_top;

  while (h != NULL)
    {
      while (h && strcmp (h->group_name, "severity") != 0)
	h = h->next;
      if (e == 0)
	return h;
      --e;
      if (h)
	h = h->next;
    }
  return h;
}