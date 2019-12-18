#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct plug_handle {void (* unplug_fn ) (struct plug_handle*) ;int /*<<< orphan*/  unplug_work; TYPE_1__ unplug_timer; scalar_t__ unplug_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  plugger_timeout ; 
 int /*<<< orphan*/  plugger_work ; 

void plugger_init(struct plug_handle *plug,
		  void (*unplug_fn)(struct plug_handle *))
{
	plug->unplug_flag = 0;
	plug->unplug_fn = unplug_fn;
	init_timer(&plug->unplug_timer);
	plug->unplug_timer.function = plugger_timeout;
	plug->unplug_timer.data = (unsigned long)plug;
	INIT_WORK(&plug->unplug_work, plugger_work);
}