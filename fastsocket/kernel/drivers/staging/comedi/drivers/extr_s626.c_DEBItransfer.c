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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC2_UPLD_DEBI ; 
 int /*<<< orphan*/  MC_ENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC_TEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PSR_DEBI_S ; 
 int /*<<< orphan*/  P_MC2 ; 
 int /*<<< orphan*/  P_PSR ; 
 int RR7146 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DEBItransfer(struct comedi_device *dev)
{
	/*  Initiate upload of shadow RAM to DEBI control register. */
	MC_ENABLE(P_MC2, MC2_UPLD_DEBI);

	/*  Wait for completion of upload from shadow RAM to DEBI control */
	/*  register. */
	while (!MC_TEST(P_MC2, MC2_UPLD_DEBI)) ;

	/*  Wait until DEBI transfer is done. */
	while (RR7146(P_PSR) & PSR_DEBI_S) ;
}