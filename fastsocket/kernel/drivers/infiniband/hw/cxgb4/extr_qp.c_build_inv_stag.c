#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ r2; int /*<<< orphan*/  stag_inv; } ;
union t4_wr {TYPE_2__ inv; } ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  invalidate_rkey; } ;
struct ib_send_wr {TYPE_1__ ex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_inv_stag(union t4_wr *wqe, struct ib_send_wr *wr,
			  u8 *len16)
{
	wqe->inv.stag_inv = cpu_to_be32(wr->ex.invalidate_rkey);
	wqe->inv.r2 = 0;
	*len16 = DIV_ROUND_UP(sizeof wqe->inv, 16);
	return 0;
}