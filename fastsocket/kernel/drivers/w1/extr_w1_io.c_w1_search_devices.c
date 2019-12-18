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
typedef  int /*<<< orphan*/  w1_slave_found_callback ;
typedef  int /*<<< orphan*/  u8 ;
struct w1_master {TYPE_1__* bus_master; int /*<<< orphan*/  attempts; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* search ) (int /*<<< orphan*/ ,struct w1_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct w1_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w1_search (struct w1_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void w1_search_devices(struct w1_master *dev, u8 search_type, w1_slave_found_callback cb)
{
	dev->attempts++;
	if (dev->bus_master->search)
		dev->bus_master->search(dev->bus_master->data, dev,
			search_type, cb);
	else
		w1_search(dev, search_type, cb);
}