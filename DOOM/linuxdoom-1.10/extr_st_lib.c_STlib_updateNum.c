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
struct TYPE_4__ {scalar_t__* on; } ;
typedef  TYPE_1__ st_number_t ;
typedef  int /*<<< orphan*/  boolean ;

/* Variables and functions */
 int /*<<< orphan*/  STlib_drawNum (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
STlib_updateNum
( st_number_t*		n,
  boolean		refresh )
{
    if (*n->on) STlib_drawNum(n, refresh);
}