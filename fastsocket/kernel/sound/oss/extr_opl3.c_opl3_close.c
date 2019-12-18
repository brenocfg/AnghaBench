#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ perc_mode; scalar_t__ nr_drums; } ;
struct TYPE_6__ {int nr_voice; int model; TYPE_2__ fm_info; TYPE_1__* v_alloc; scalar_t__ busy; } ;
struct TYPE_4__ {int max_voice; } ;

/* Variables and functions */
 TYPE_3__* devc ; 
 int /*<<< orphan*/  opl3_reset (int) ; 

__attribute__((used)) static void opl3_close(int dev)
{
	devc->busy = 0;
	devc->v_alloc->max_voice = devc->nr_voice = (devc->model == 2) ? 18 : 9;

	devc->fm_info.nr_drums = 0;
	devc->fm_info.perc_mode = 0;

	opl3_reset(dev);
}