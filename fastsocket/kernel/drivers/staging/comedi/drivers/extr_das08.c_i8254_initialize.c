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
struct i8254_struct {int /*<<< orphan*/ * mode; int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  i8254_set_mode_low (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i8254_initialize(struct i8254_struct *st)
{
	int i;
	for (i = 0; i < 3; ++i)
		i8254_set_mode_low(st->iobase, i, st->mode[i]);
}