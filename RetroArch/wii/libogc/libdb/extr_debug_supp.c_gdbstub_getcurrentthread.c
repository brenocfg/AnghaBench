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
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 TYPE_2__* _thr_executing ; 
 int /*<<< orphan*/  gdbstub_idtoindex (int /*<<< orphan*/ ) ; 

s32 gdbstub_getcurrentthread()
{
	return gdbstub_idtoindex(_thr_executing->object.id);
}