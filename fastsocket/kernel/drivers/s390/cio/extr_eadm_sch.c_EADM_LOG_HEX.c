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
struct TYPE_3__ {int level; scalar_t__ buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_event (TYPE_1__*,int,void*,int) ; 
 TYPE_1__* eadm_debug ; 

__attribute__((used)) static void EADM_LOG_HEX(int level, void *data, int length)
{
	if (level > eadm_debug->level)
		return;
	while (length > 0) {
		debug_event(eadm_debug, level, data, length);
		length -= eadm_debug->buf_size;
		data += eadm_debug->buf_size;
	}
}