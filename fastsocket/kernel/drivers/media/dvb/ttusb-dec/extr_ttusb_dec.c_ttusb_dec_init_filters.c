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
struct ttusb_dec {int /*<<< orphan*/  filter_info_list_lock; int /*<<< orphan*/  filter_info_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ttusb_dec_init_filters(struct ttusb_dec *dec)
{
	INIT_LIST_HEAD(&dec->filter_info_list);
	spin_lock_init(&dec->filter_info_list_lock);
}