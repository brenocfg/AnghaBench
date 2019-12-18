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
struct westwood {int /*<<< orphan*/  rtt_min; int /*<<< orphan*/  rtt; scalar_t__ reset_rtt_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void update_rtt_min(struct westwood *w)
{
	if (w->reset_rtt_min) {
		w->rtt_min = w->rtt;
		w->reset_rtt_min = 0;
	} else
		w->rtt_min = min(w->rtt, w->rtt_min);
}