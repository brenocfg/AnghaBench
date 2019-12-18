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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u16 ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  NES_DBG_INIT ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int nes_multicast_attach(struct ib_qp *ibqp, union ib_gid *gid, u16 lid)
{
	nes_debug(NES_DBG_INIT, "\n");
	return -ENOSYS;
}