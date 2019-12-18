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
struct tfrc_rx_hist_entry {int dummy; } ;
struct tfrc_rx_hist {int /*<<< orphan*/  loss_count; struct tfrc_rx_hist_entry** ring; } ;

/* Variables and functions */
 size_t tfrc_rx_hist_index (struct tfrc_rx_hist const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct tfrc_rx_hist_entry *
			tfrc_rx_hist_last_rcv(const struct tfrc_rx_hist *h)
{
	return h->ring[tfrc_rx_hist_index(h, h->loss_count)];
}