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
struct ad7879 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad7879_ts_event_release (struct ad7879*) ; 

__attribute__((used)) static void ad7879_timer(unsigned long handle)
{
	struct ad7879 *ts = (void *)handle;

	ad7879_ts_event_release(ts);
}