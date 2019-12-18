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
struct channel_info {int /*<<< orphan*/  header_pg; int /*<<< orphan*/  header_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int get_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poch_channel_free_header(struct channel_info *channel)
{
	unsigned int order;

	order = get_order(channel->header_size);
	__free_pages(channel->header_pg, order);
}