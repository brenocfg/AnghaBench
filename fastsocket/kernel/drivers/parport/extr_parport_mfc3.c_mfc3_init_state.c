#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int datadir; int statusdir; scalar_t__ status; scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ amiga; } ;
struct parport_state {TYPE_2__ u; } ;
struct pardevice {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void mfc3_init_state(struct pardevice *dev, struct parport_state *s)
{
	s->u.amiga.data = 0;
	s->u.amiga.datadir = 255;
	s->u.amiga.status = 0;
	s->u.amiga.statusdir = 0xe0;
}