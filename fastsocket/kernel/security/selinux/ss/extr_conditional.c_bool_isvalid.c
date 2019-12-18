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
struct cond_bool_datum {int state; } ;

/* Variables and functions */

__attribute__((used)) static int bool_isvalid(struct cond_bool_datum *b)
{
	if (!(b->state == 0 || b->state == 1))
		return 0;
	return 1;
}