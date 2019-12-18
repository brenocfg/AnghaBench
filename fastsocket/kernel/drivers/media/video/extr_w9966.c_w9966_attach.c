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
struct parport {char* name; } ;
struct TYPE_4__ {scalar_t__ dev_state; } ;

/* Variables and functions */
 int W9966_MAXCAMS ; 
 int /*<<< orphan*/ * pardev ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* w9966_cams ; 
 scalar_t__ w9966_init (TYPE_1__*,struct parport*) ; 
 int /*<<< orphan*/  w9966_term (TYPE_1__*) ; 

__attribute__((used)) static void w9966_attach(struct parport *port)
{
	int i;

	for (i = 0; i < W9966_MAXCAMS; i++)
	{
		if (w9966_cams[i].dev_state != 0)	// Cam is already assigned
			continue;
		if (
			strcmp(pardev[i], "aggressive") == 0 ||
			strcmp(pardev[i], port->name) == 0
		) {
			if (w9966_init(&w9966_cams[i], port) != 0)
			w9966_term(&w9966_cams[i]);
			break;	// return
		}
	}
}