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
struct ring_buffer {unsigned long pages; } ;

/* Variables and functions */
 unsigned long BUF_PAGE_SIZE ; 

unsigned long ring_buffer_size(struct ring_buffer *buffer)
{
	return BUF_PAGE_SIZE * buffer->pages;
}