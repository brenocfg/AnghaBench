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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  mite_csigr_dmac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_csigr_imode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_csigr_iowins (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_csigr_mmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_csigr_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_csigr_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_csigr_wins (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_csigr_wpdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_chip_signature(u32 csigr_bits)
{
	printk
	    ("mite: version = %i, type = %i, mite mode = %i, interface mode = %i\n",
	     mite_csigr_version(csigr_bits), mite_csigr_type(csigr_bits),
	     mite_csigr_mmode(csigr_bits), mite_csigr_imode(csigr_bits));
	printk
	    ("mite: num channels = %i, write post fifo depth = %i, wins = %i, iowins = %i\n",
	     mite_csigr_dmac(csigr_bits), mite_csigr_wpdep(csigr_bits),
	     mite_csigr_wins(csigr_bits), mite_csigr_iowins(csigr_bits));
}