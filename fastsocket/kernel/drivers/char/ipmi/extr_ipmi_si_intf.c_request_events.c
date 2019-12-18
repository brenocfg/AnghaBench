#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct smi_info {int /*<<< orphan*/  req_events; int /*<<< orphan*/  has_event_buffer; int /*<<< orphan*/  stop_operation; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void request_events(void *send_info)
{
	struct smi_info *smi_info = send_info;

	if (atomic_read(&smi_info->stop_operation) ||
				!smi_info->has_event_buffer)
		return;

	atomic_set(&smi_info->req_events, 1);
}