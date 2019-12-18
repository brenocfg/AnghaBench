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
struct gs_buf {int buf_size; int buf_get; int buf_put; } ;

/* Variables and functions */

__attribute__((used)) static unsigned gs_buf_space_avail(struct gs_buf *gb)
{
	return (gb->buf_size + gb->buf_get - gb->buf_put - 1) % gb->buf_size;
}