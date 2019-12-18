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
typedef  int u64 ;
struct niu {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZCP_RAM_ACC ; 
 int /*<<< orphan*/  ZCP_RAM_ACC_BUSY ; 
 int ZCP_RAM_ACC_RAM_SEL_SHIFT ; 
 int ZCP_RAM_ACC_WRITE ; 
 int ZCP_RAM_ACC_ZFCID_SHIFT ; 
 int /*<<< orphan*/  ZCP_RAM_BE ; 
 int ZCP_RAM_BE_VAL ; 
 int /*<<< orphan*/  ZCP_RAM_DATA0 ; 
 int /*<<< orphan*/  ZCP_RAM_DATA1 ; 
 int /*<<< orphan*/  ZCP_RAM_DATA2 ; 
 int /*<<< orphan*/  ZCP_RAM_DATA3 ; 
 int /*<<< orphan*/  ZCP_RAM_DATA4 ; 
 int ZCP_RAM_SEL_CFIFO (int /*<<< orphan*/ ) ; 
 int niu_wait_bits_clear (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int niu_zcp_write(struct niu *np, int index, u64 *data)
{
	nw64(ZCP_RAM_DATA0, data[0]);
	nw64(ZCP_RAM_DATA1, data[1]);
	nw64(ZCP_RAM_DATA2, data[2]);
	nw64(ZCP_RAM_DATA3, data[3]);
	nw64(ZCP_RAM_DATA4, data[4]);
	nw64(ZCP_RAM_BE, ZCP_RAM_BE_VAL);
	nw64(ZCP_RAM_ACC,
	     (ZCP_RAM_ACC_WRITE |
	      (0 << ZCP_RAM_ACC_ZFCID_SHIFT) |
	      (ZCP_RAM_SEL_CFIFO(np->port) << ZCP_RAM_ACC_RAM_SEL_SHIFT)));

	return niu_wait_bits_clear(np, ZCP_RAM_ACC, ZCP_RAM_ACC_BUSY,
				   1000, 100);
}