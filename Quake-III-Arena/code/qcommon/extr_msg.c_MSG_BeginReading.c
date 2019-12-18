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
struct TYPE_3__ {int /*<<< orphan*/  oob; scalar_t__ bit; scalar_t__ readcount; } ;
typedef  TYPE_1__ msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  qfalse ; 

void MSG_BeginReading( msg_t *msg ) {
	msg->readcount = 0;
	msg->bit = 0;
	msg->oob = qfalse;
}