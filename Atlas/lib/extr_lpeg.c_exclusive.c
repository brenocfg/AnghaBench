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
struct TYPE_4__ {scalar_t__ tag; int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ CharsetTag ;

/* Variables and functions */
 scalar_t__ NOINFO ; 
 int exclusiveset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exclusive (CharsetTag *c1, CharsetTag *c2) {
  if (c1->tag == NOINFO || c2->tag == NOINFO)
    return 0;  /* one of them is not filled */
  else return exclusiveset(c1->cs, c2->cs);
}