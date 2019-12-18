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
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPP_CFIG ; 
 int IPP_CFIG_DFIFO_PIO_W ; 
 int /*<<< orphan*/  IPP_DFIFO_WR0 ; 
 int /*<<< orphan*/  IPP_DFIFO_WR1 ; 
 int /*<<< orphan*/  IPP_DFIFO_WR2 ; 
 int /*<<< orphan*/  IPP_DFIFO_WR3 ; 
 int /*<<< orphan*/  IPP_DFIFO_WR4 ; 
 int /*<<< orphan*/  IPP_DFIFO_WR_PTR ; 
 int nr64_ipp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_ipp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void niu_ipp_write(struct niu *np, int index, u64 *data)
{
	u64 val = nr64_ipp(IPP_CFIG);

	nw64_ipp(IPP_CFIG, val | IPP_CFIG_DFIFO_PIO_W);
	nw64_ipp(IPP_DFIFO_WR_PTR, index);
	nw64_ipp(IPP_DFIFO_WR0, data[0]);
	nw64_ipp(IPP_DFIFO_WR1, data[1]);
	nw64_ipp(IPP_DFIFO_WR2, data[2]);
	nw64_ipp(IPP_DFIFO_WR3, data[3]);
	nw64_ipp(IPP_DFIFO_WR4, data[4]);
	nw64_ipp(IPP_CFIG, val & ~IPP_CFIG_DFIFO_PIO_W);
}