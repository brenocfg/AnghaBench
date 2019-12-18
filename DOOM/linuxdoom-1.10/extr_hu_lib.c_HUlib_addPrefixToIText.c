#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
struct TYPE_4__ {TYPE_3__ l; int /*<<< orphan*/  lm; } ;
typedef  TYPE_1__ hu_itext_t ;

/* Variables and functions */
 int /*<<< orphan*/  HUlib_addCharToTextLine (TYPE_3__*,int /*<<< orphan*/ ) ; 

void
HUlib_addPrefixToIText
( hu_itext_t*	it,
  char*		str )
{
    while (*str)
	HUlib_addCharToTextLine(&it->l, *(str++));
    it->lm = it->l.len;
}