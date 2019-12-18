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
struct socket_buffer {int /*<<< orphan*/  start; int /*<<< orphan*/  read; } ;

/* Variables and functions */

void netplay_recv_reset(struct socket_buffer *sbuf)
{
   sbuf->read = sbuf->start;
}