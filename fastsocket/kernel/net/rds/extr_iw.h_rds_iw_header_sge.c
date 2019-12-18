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
struct rds_iw_connection {int dummy; } ;
struct ib_sge {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ib_sge *
rds_iw_header_sge(struct rds_iw_connection *ic, struct ib_sge *sge)
{
	return &sge[0];
}