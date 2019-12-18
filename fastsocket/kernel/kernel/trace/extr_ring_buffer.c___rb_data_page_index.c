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
struct buffer_data_page {void* data; } ;

/* Variables and functions */

__attribute__((used)) static inline void *
__rb_data_page_index(struct buffer_data_page *bpage, unsigned index)
{
	return bpage->data + index;
}