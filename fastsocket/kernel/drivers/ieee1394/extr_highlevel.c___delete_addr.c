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
struct hpsb_address_serve {int /*<<< orphan*/  hl_list; int /*<<< orphan*/  host_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hpsb_address_serve*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __delete_addr(struct hpsb_address_serve *as)
{
	list_del(&as->host_list);
	list_del(&as->hl_list);
	kfree(as);
}