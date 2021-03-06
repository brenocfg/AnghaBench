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
struct circ_buf {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int CIRC_CNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_WRITE_BUF_SIZE ; 

__attribute__((used)) static int ti_buf_data_avail(struct circ_buf *cb)
{
	return CIRC_CNT(cb->head, cb->tail, TI_WRITE_BUF_SIZE);
}