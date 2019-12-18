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
struct edge_buf {unsigned int buf_size; unsigned int buf_put; unsigned int buf_get; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int edge_buf_data_avail(struct edge_buf *eb)
{
	if (eb == NULL)
		return 0;
	return ((eb->buf_size + eb->buf_put - eb->buf_get) % eb->buf_size);
}