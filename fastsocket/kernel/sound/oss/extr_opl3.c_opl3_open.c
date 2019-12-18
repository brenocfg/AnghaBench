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
struct TYPE_4__ {int busy; int nr_voice; int model; int cmask; int /*<<< orphan*/  right_io; TYPE_1__* v_alloc; } ;
struct TYPE_3__ {int max_voice; scalar_t__* alloc_times; scalar_t__* map; scalar_t__ timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_SELECT_REGISTER ; 
 int EBUSY ; 
 TYPE_2__* devc ; 
 int /*<<< orphan*/  opl3_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int opl3_open(int dev, int mode)
{
	int i;

	if (devc->busy)
		return -EBUSY;
	devc->busy = 1;

	devc->v_alloc->max_voice = devc->nr_voice = (devc->model == 2) ? 18 : 9;
	devc->v_alloc->timestamp = 0;

	for (i = 0; i < 18; i++)
	{
		devc->v_alloc->map[i] = 0;
		devc->v_alloc->alloc_times[i] = 0;
	}

	devc->cmask = 0x00;	/*
				 * Just 2 OP mode
				 */
	if (devc->model == 2)
		opl3_command(devc->right_io, CONNECTION_SELECT_REGISTER, devc->cmask);
	return 0;
}