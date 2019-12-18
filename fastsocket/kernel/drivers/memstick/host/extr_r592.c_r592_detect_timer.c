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
struct r592_device {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  memstick_detect_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_update_card_detect (struct r592_device*) ; 

__attribute__((used)) static void r592_detect_timer(long unsigned int data)
{
	struct r592_device *dev = (struct r592_device *)data;
	r592_update_card_detect(dev);
	memstick_detect_change(dev->host);
}