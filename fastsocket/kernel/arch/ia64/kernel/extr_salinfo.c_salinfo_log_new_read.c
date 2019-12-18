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
struct salinfo_data_saved {int cpu; scalar_t__ id; int /*<<< orphan*/  size; scalar_t__ buffer; } ;
struct salinfo_data {int saved_num; int /*<<< orphan*/  state; int /*<<< orphan*/  cpu_event; int /*<<< orphan*/  log_size; int /*<<< orphan*/  log_buffer; struct salinfo_data_saved* data_saved; } ;
struct TYPE_3__ {scalar_t__ id; } ;
typedef  TYPE_1__ sal_log_record_header_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct salinfo_data_saved*) ; 
 int /*<<< orphan*/  STATE_LOG_RECORD ; 
 int /*<<< orphan*/  STATE_NO_DATA ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  call_on_cpu (int,int /*<<< orphan*/ ,struct salinfo_data*) ; 
 int /*<<< orphan*/  cpu_clear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_saved_lock ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  salinfo_log_read_cpu ; 
 int /*<<< orphan*/  shift1_data_saved (struct salinfo_data*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
salinfo_log_new_read(int cpu, struct salinfo_data *data)
{
	struct salinfo_data_saved *data_saved;
	unsigned long flags;
	int i;
	int saved_size = ARRAY_SIZE(data->data_saved);

	data->saved_num = 0;
	spin_lock_irqsave(&data_saved_lock, flags);
retry:
	for (i = 0, data_saved = data->data_saved; i < saved_size; ++i, ++data_saved) {
		if (data_saved->buffer && data_saved->cpu == cpu) {
			sal_log_record_header_t *rh = (sal_log_record_header_t *)(data_saved->buffer);
			data->log_size = data_saved->size;
			memcpy(data->log_buffer, rh, data->log_size);
			barrier();	/* id check must not be moved */
			if (rh->id == data_saved->id) {
				data->saved_num = i+1;
				break;
			}
			/* saved record changed by mca.c since interrupt, discard it */
			shift1_data_saved(data, i);
			goto retry;
		}
	}
	spin_unlock_irqrestore(&data_saved_lock, flags);

	if (!data->saved_num)
		call_on_cpu(cpu, salinfo_log_read_cpu, data);
	if (!data->log_size) {
		data->state = STATE_NO_DATA;
		cpu_clear(cpu, data->cpu_event);
	} else {
		data->state = STATE_LOG_RECORD;
	}
}