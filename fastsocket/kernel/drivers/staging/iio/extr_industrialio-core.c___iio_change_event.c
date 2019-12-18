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
struct TYPE_2__ {int id; int /*<<< orphan*/  timestamp; } ;
struct iio_detected_event_list {TYPE_1__ ev; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */

void __iio_change_event(struct iio_detected_event_list *ev,
			int ev_code,
			s64 timestamp)
{
	ev->ev.id = ev_code;
	ev->ev.timestamp = timestamp;
}