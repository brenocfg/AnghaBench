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
struct slip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sl_lock(struct slip *sl)
{
	netif_stop_queue(sl->dev);
}