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
struct TYPE_3__ {scalar_t__ buf_size; } ;

/* Variables and functions */
 TYPE_1__* chsc_debug_log_id ; 
 int /*<<< orphan*/  debug_event (TYPE_1__*,int,void*,int) ; 

__attribute__((used)) static void CHSC_LOG_HEX(int level, void *data, int length)
{
	while (length > 0) {
		debug_event(chsc_debug_log_id, level, data, length);
		length -= chsc_debug_log_id->buf_size;
		data += chsc_debug_log_id->buf_size;
	}
}