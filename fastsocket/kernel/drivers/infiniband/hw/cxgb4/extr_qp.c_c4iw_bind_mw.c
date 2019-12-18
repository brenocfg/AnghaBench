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
struct ib_qp {int dummy; } ;
struct ib_mw_bind {int dummy; } ;
struct ib_mw {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

int c4iw_bind_mw(struct ib_qp *qp, struct ib_mw *mw, struct ib_mw_bind *mw_bind)
{
	return -ENOSYS;
}