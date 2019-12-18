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
struct parport {int dummy; } ;
struct TYPE_3__ {scalar_t__ dev_state; struct parport* pport; } ;

/* Variables and functions */
 int W9966_MAXCAMS ; 
 TYPE_1__* w9966_cams ; 
 int /*<<< orphan*/  w9966_term (TYPE_1__*) ; 

__attribute__((used)) static void w9966_detach(struct parport *port)
{
	int i;
	for (i = 0; i < W9966_MAXCAMS; i++)
	if (w9966_cams[i].dev_state != 0 && w9966_cams[i].pport == port)
		w9966_term(&w9966_cams[i]);
}