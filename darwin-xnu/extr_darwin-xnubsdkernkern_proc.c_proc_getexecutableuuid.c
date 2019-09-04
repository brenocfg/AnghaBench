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
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 

void
proc_getexecutableuuid(proc_t p, unsigned char *uuidbuf, unsigned long size)
{
	if (size >= sizeof(p->p_uuid)) {
		memcpy(uuidbuf, p->p_uuid, sizeof(p->p_uuid));
	}
}