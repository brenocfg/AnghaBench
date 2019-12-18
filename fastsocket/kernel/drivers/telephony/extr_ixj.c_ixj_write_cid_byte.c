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
struct TYPE_3__ {scalar_t__ b7; scalar_t__ b6; scalar_t__ b5; scalar_t__ b4; scalar_t__ b3; scalar_t__ b2; scalar_t__ b1; scalar_t__ b0; } ;
struct TYPE_4__ {char cbyte; TYPE_1__ cbits; } ;
typedef  TYPE_2__ IXJ_CBYTE ;
typedef  int /*<<< orphan*/  IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  ixj_write_cid_bit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ixj_write_cid_byte(IXJ *j, char byte)
{
	IXJ_CBYTE cb;

		cb.cbyte = byte;
		ixj_write_cid_bit(j, 0);
		ixj_write_cid_bit(j, cb.cbits.b0 ? 1 : 0);
		ixj_write_cid_bit(j, cb.cbits.b1 ? 1 : 0);
		ixj_write_cid_bit(j, cb.cbits.b2 ? 1 : 0);
		ixj_write_cid_bit(j, cb.cbits.b3 ? 1 : 0);
		ixj_write_cid_bit(j, cb.cbits.b4 ? 1 : 0);
		ixj_write_cid_bit(j, cb.cbits.b5 ? 1 : 0);
		ixj_write_cid_bit(j, cb.cbits.b6 ? 1 : 0);
		ixj_write_cid_bit(j, cb.cbits.b7 ? 1 : 0);
		ixj_write_cid_bit(j, 1);
}