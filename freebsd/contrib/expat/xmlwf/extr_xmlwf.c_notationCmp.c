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
struct TYPE_2__ {int /*<<< orphan*/  notationName; } ;
typedef  TYPE_1__ NotationList ;

/* Variables and functions */
 int xcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
notationCmp(const void *a, const void *b)
{
  const NotationList * const n1 = *(NotationList **)a;
  const NotationList * const n2 = *(NotationList **)b;

  return xcscmp(n1->notationName, n2->notationName);
}