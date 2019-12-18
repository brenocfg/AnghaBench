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
struct qdio_q {int dummy; } ;

/* Variables and functions */
 int get_buf_states (struct qdio_q*,unsigned int,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdio_siga_sync_q (struct qdio_q*) ; 

int debug_get_buf_state(struct qdio_q *q, unsigned int bufnr,
			unsigned char *state)
{
	qdio_siga_sync_q(q);
	return get_buf_states(q, bufnr, state, 1, 0, 0);
}