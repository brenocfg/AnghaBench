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

/* Variables and functions */
 int EV6__D_STAT__ECC_ERR_LD ; 
 int EV6__D_STAT__ECC_ERR_ST ; 
 int EV6__D_STAT__ERRMASK ; 
 int EV6__D_STAT__SEO ; 
 int EV6__D_STAT__TPERR_P0 ; 
 int EV6__D_STAT__TPERR_P1 ; 
 int EV6__MM_STAT__DC_TAG_PERR ; 
 int EV6__MM_STAT__ERRMASK ; 
 int MCHK_DISPOSITION_REPORT ; 
 int MCHK_DISPOSITION_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
ev6_parse_mbox(u64 mm_stat, u64 d_stat, u64 c_stat, int print)
{
	int status = MCHK_DISPOSITION_REPORT;

#define EV6__MM_STAT__DC_TAG_PERR	(1UL << 10)
#define EV6__MM_STAT__ERRMASK		(EV6__MM_STAT__DC_TAG_PERR)
#define EV6__D_STAT__TPERR_P0		(1UL << 0)
#define EV6__D_STAT__TPERR_P1		(1UL << 1)
#define EV6__D_STAT__ECC_ERR_ST		(1UL << 2)
#define EV6__D_STAT__ECC_ERR_LD		(1UL << 3)
#define EV6__D_STAT__SEO		(1UL << 4)
#define EV6__D_STAT__ERRMASK		(EV6__D_STAT__TPERR_P0 |	\
                                         EV6__D_STAT__TPERR_P1 | 	\
                                         EV6__D_STAT__ECC_ERR_ST | 	\
                                         EV6__D_STAT__ECC_ERR_LD | 	\
                                         EV6__D_STAT__SEO)

	if (!(d_stat & EV6__D_STAT__ERRMASK) && 
	    !(mm_stat & EV6__MM_STAT__ERRMASK))
		return MCHK_DISPOSITION_UNKNOWN_ERROR;

	if (!print)
		return status;

	if (mm_stat & EV6__MM_STAT__DC_TAG_PERR)
		printk("%s    Dcache tag parity error on probe\n",
		       err_print_prefix);
	if (d_stat & EV6__D_STAT__TPERR_P0)
		printk("%s    Dcache tag parity error - pipe 0\n",
		       err_print_prefix);
	if (d_stat & EV6__D_STAT__TPERR_P1)
		printk("%s    Dcache tag parity error - pipe 1\n",
		       err_print_prefix);
	if (d_stat & EV6__D_STAT__ECC_ERR_ST)
		printk("%s    ECC error occurred on a store\n", 
		       err_print_prefix);
	if (d_stat & EV6__D_STAT__ECC_ERR_LD)
		printk("%s    ECC error occurred on a %s load\n",
		       err_print_prefix,
		       c_stat ? "" : "speculative ");
	if (d_stat & EV6__D_STAT__SEO)
		printk("%s    Dcache second error\n", err_print_prefix);

	return status;
}