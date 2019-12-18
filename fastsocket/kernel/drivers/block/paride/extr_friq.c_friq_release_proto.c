#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ private; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (int) ; 
 int /*<<< orphan*/  friq_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  friq_disconnect (TYPE_1__*) ; 

__attribute__((used)) static void friq_release_proto( PIA *pi)
{
	if (pi->private) {		/* turn off the power */
		friq_connect(pi);
		CMD(0x1d); CMD(0x1e);
		friq_disconnect(pi);
		pi->private = 0;
	}
}