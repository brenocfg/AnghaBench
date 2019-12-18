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
struct file {void* private_data; } ;
typedef  int /*<<< orphan*/  dword ;
struct TYPE_4__ {unsigned long data; void* function; } ;
struct TYPE_3__ {int adapter_nr; scalar_t__ aborted; TYPE_2__ diva_timer_id; int /*<<< orphan*/  close_wait; int /*<<< orphan*/  read_wait; } ;
typedef  TYPE_1__ diva_um_idi_os_context_t ;

/* Variables and functions */
 scalar_t__ diva_um_id_get_os_context (void*) ; 
 scalar_t__ diva_um_timer_function ; 
 void* divas_um_idi_create_entity (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int um_idi_open_adapter(struct file *file, int adapter_nr)
{
	diva_um_idi_os_context_t *p_os;
	void *e =
	    divas_um_idi_create_entity((dword) adapter_nr, (void *) file);

	if (!(file->private_data = e)) {
		return (0);
	}
	p_os = (diva_um_idi_os_context_t *) diva_um_id_get_os_context(e);
	init_waitqueue_head(&p_os->read_wait);
	init_waitqueue_head(&p_os->close_wait);
	init_timer(&p_os->diva_timer_id);
	p_os->diva_timer_id.function = (void *) diva_um_timer_function;
	p_os->diva_timer_id.data = (unsigned long) p_os;
	p_os->aborted = 0;
	p_os->adapter_nr = adapter_nr;
	return (1);
}