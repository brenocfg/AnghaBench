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
struct mlx4_cq_context {int log_page_size; int /*<<< orphan*/  logsize_usrpage; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cq_get_mtt_size(struct mlx4_cq_context *cqc)
{
	int log_cq_size = (be32_to_cpu(cqc->logsize_usrpage) >> 24) & 0x1f;
	int page_shift = (cqc->log_page_size & 0x3f) + 12;

	if (log_cq_size + 5 < page_shift)
		return 1;

	return 1 << (log_cq_size + 5 - page_shift);
}