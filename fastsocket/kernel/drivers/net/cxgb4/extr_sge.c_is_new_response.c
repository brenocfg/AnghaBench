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
struct sge_rspq {scalar_t__ gen; } ;
struct rsp_ctrl {int /*<<< orphan*/  type_gen; } ;

/* Variables and functions */
 scalar_t__ RSPD_GEN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_new_response(const struct rsp_ctrl *r,
				   const struct sge_rspq *q)
{
	return RSPD_GEN(r->type_gen) == q->gen;
}