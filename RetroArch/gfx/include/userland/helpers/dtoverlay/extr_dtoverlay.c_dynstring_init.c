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
struct dynstring {int /*<<< orphan*/ * buf; scalar_t__ len; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static void dynstring_init(struct dynstring *ds)
{
   ds->size = 0;
   ds->len = 0;
   ds->buf = NULL;
}