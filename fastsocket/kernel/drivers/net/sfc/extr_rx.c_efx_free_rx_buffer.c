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
struct efx_rx_buffer {int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_free_rx_buffer(struct efx_rx_buffer *rx_buf)
{
	if (rx_buf->page) {
		put_page(rx_buf->page);
		rx_buf->page = NULL;
	}
}