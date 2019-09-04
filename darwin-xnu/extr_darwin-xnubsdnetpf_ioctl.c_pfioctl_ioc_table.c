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
typedef  int u_long ;
struct proc {int dummy; } ;
struct pfr_tstats {int dummy; } ;
struct pfr_table {int dummy; } ;
struct pfr_astats {int dummy; } ;
struct pfr_addr {int dummy; } ;
struct pfioc_table_64 {int pfrio_esize; int pfrio_flags; int /*<<< orphan*/  pfrio_ticket; int /*<<< orphan*/  pfrio_naddr; int /*<<< orphan*/  pfrio_nadd; int /*<<< orphan*/  pfrio_size; int /*<<< orphan*/  pfrio_buffer; int /*<<< orphan*/  pfrio_table; int /*<<< orphan*/  pfrio_nmatch; int /*<<< orphan*/  pfrio_nzero; int /*<<< orphan*/  pfrio_nchange; int /*<<< orphan*/  pfrio_ndel; int /*<<< orphan*/  pfrio_size2; int /*<<< orphan*/  pfrio_clrflag; int /*<<< orphan*/  pfrio_setflag; } ;
struct pfioc_table_32 {int pfrio_esize; int pfrio_flags; int /*<<< orphan*/  pfrio_ticket; int /*<<< orphan*/  pfrio_naddr; int /*<<< orphan*/  pfrio_nadd; int /*<<< orphan*/  pfrio_size; int /*<<< orphan*/  pfrio_buffer; int /*<<< orphan*/  pfrio_table; int /*<<< orphan*/  pfrio_nmatch; int /*<<< orphan*/  pfrio_nzero; int /*<<< orphan*/  pfrio_nchange; int /*<<< orphan*/  pfrio_ndel; int /*<<< orphan*/  pfrio_size2; int /*<<< orphan*/  pfrio_clrflag; int /*<<< orphan*/  pfrio_setflag; } ;

/* Variables and functions */
#define  DIOCRADDADDRS 143 
#define  DIOCRADDTABLES 142 
#define  DIOCRCLRADDRS 141 
#define  DIOCRCLRASTATS 140 
#define  DIOCRCLRTABLES 139 
#define  DIOCRCLRTSTATS 138 
#define  DIOCRDELADDRS 137 
#define  DIOCRDELTABLES 136 
#define  DIOCRGETADDRS 135 
#define  DIOCRGETASTATS 134 
#define  DIOCRGETTABLES 133 
#define  DIOCRGETTSTATS 132 
#define  DIOCRINADEFINE 131 
#define  DIOCRSETADDRS 130 
#define  DIOCRSETTFLAGS 129 
#define  DIOCRTSTADDRS 128 
 int ENODEV ; 
 int PFR_FLAG_USERIOCTL ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int pfr_add_addrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pfr_add_tables (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pfr_clr_addrs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pfr_clr_astats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pfr_clr_tables (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pfr_clr_tstats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pfr_del_addrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pfr_del_tables (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pfr_get_addrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pfr_get_astats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pfr_get_tables (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pfr_get_tstats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pfr_ina_define (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int pfr_set_addrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int pfr_set_tflags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pfr_table_copyin_cleanup (int /*<<< orphan*/ *) ; 
 int pfr_tst_addrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int proc_is64bit (struct proc*) ; 

__attribute__((used)) static int
pfioctl_ioc_table(u_long cmd, struct pfioc_table_32 *io32,
    struct pfioc_table_64 *io64, struct proc *p)
{
	int p64 = proc_is64bit(p);
	int error = 0;

	if (!p64)
		goto struct32;

	/*
	 * 64-bit structure processing
	 */
	switch (cmd) {
	case DIOCRCLRTABLES:
		if (io64->pfrio_esize != 0) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_clr_tables(&io64->pfrio_table, &io64->pfrio_ndel,
		    io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRADDTABLES:
		if (io64->pfrio_esize != sizeof (struct pfr_table)) {
			error = ENODEV;
			break;
		}
		error = pfr_add_tables(io64->pfrio_buffer, io64->pfrio_size,
		    &io64->pfrio_nadd, io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRDELTABLES:
		if (io64->pfrio_esize != sizeof (struct pfr_table)) {
			error = ENODEV;
			break;
		}
		error = pfr_del_tables(io64->pfrio_buffer, io64->pfrio_size,
		    &io64->pfrio_ndel, io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRGETTABLES:
		if (io64->pfrio_esize != sizeof (struct pfr_table)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_get_tables(&io64->pfrio_table, io64->pfrio_buffer,
		    &io64->pfrio_size, io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRGETTSTATS:
		if (io64->pfrio_esize != sizeof (struct pfr_tstats)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_get_tstats(&io64->pfrio_table, io64->pfrio_buffer,
		    &io64->pfrio_size, io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRCLRTSTATS:
		if (io64->pfrio_esize != sizeof (struct pfr_table)) {
			error = ENODEV;
			break;
		}
		error = pfr_clr_tstats(io64->pfrio_buffer, io64->pfrio_size,
		    &io64->pfrio_nzero, io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRSETTFLAGS:
		if (io64->pfrio_esize != sizeof (struct pfr_table)) {
			error = ENODEV;
			break;
		}
		error = pfr_set_tflags(io64->pfrio_buffer, io64->pfrio_size,
		    io64->pfrio_setflag, io64->pfrio_clrflag,
		    &io64->pfrio_nchange, &io64->pfrio_ndel,
		    io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRCLRADDRS:
		if (io64->pfrio_esize != 0) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_clr_addrs(&io64->pfrio_table, &io64->pfrio_ndel,
		    io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRADDADDRS:
		if (io64->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_add_addrs(&io64->pfrio_table, io64->pfrio_buffer,
		    io64->pfrio_size, &io64->pfrio_nadd, io64->pfrio_flags |
		    PFR_FLAG_USERIOCTL);
		break;

	case DIOCRDELADDRS:
		if (io64->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_del_addrs(&io64->pfrio_table, io64->pfrio_buffer,
		    io64->pfrio_size, &io64->pfrio_ndel, io64->pfrio_flags |
		    PFR_FLAG_USERIOCTL);
		break;

	case DIOCRSETADDRS:
		if (io64->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_set_addrs(&io64->pfrio_table, io64->pfrio_buffer,
		    io64->pfrio_size, &io64->pfrio_size2, &io64->pfrio_nadd,
		    &io64->pfrio_ndel, &io64->pfrio_nchange, io64->pfrio_flags |
		    PFR_FLAG_USERIOCTL, 0);
		break;

	case DIOCRGETADDRS:
		if (io64->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_get_addrs(&io64->pfrio_table, io64->pfrio_buffer,
		    &io64->pfrio_size, io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRGETASTATS:
		if (io64->pfrio_esize != sizeof (struct pfr_astats)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_get_astats(&io64->pfrio_table, io64->pfrio_buffer,
		    &io64->pfrio_size, io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRCLRASTATS:
		if (io64->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_clr_astats(&io64->pfrio_table, io64->pfrio_buffer,
		    io64->pfrio_size, &io64->pfrio_nzero, io64->pfrio_flags |
		    PFR_FLAG_USERIOCTL);
		break;

	case DIOCRTSTADDRS:
		if (io64->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_tst_addrs(&io64->pfrio_table, io64->pfrio_buffer,
		    io64->pfrio_size, &io64->pfrio_nmatch, io64->pfrio_flags |
		    PFR_FLAG_USERIOCTL);
		break;

	case DIOCRINADEFINE:
		if (io64->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io64->pfrio_table);
		error = pfr_ina_define(&io64->pfrio_table, io64->pfrio_buffer,
		    io64->pfrio_size, &io64->pfrio_nadd, &io64->pfrio_naddr,
		    io64->pfrio_ticket, io64->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	default:
		VERIFY(0);
		/* NOTREACHED */
	}
	goto done;

struct32:
	/*
	 * 32-bit structure processing
	 */
	switch (cmd) {
	case DIOCRCLRTABLES:
		if (io32->pfrio_esize != 0) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_clr_tables(&io32->pfrio_table, &io32->pfrio_ndel,
		    io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRADDTABLES:
		if (io32->pfrio_esize != sizeof (struct pfr_table)) {
			error = ENODEV;
			break;
		}
		error = pfr_add_tables(io32->pfrio_buffer, io32->pfrio_size,
		    &io32->pfrio_nadd, io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRDELTABLES:
		if (io32->pfrio_esize != sizeof (struct pfr_table)) {
			error = ENODEV;
			break;
		}
		error = pfr_del_tables(io32->pfrio_buffer, io32->pfrio_size,
		    &io32->pfrio_ndel, io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRGETTABLES:
		if (io32->pfrio_esize != sizeof (struct pfr_table)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_get_tables(&io32->pfrio_table, io32->pfrio_buffer,
		    &io32->pfrio_size, io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRGETTSTATS:
		if (io32->pfrio_esize != sizeof (struct pfr_tstats)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_get_tstats(&io32->pfrio_table, io32->pfrio_buffer,
		    &io32->pfrio_size, io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRCLRTSTATS:
		if (io32->pfrio_esize != sizeof (struct pfr_table)) {
			error = ENODEV;
			break;
		}
		error = pfr_clr_tstats(io32->pfrio_buffer, io32->pfrio_size,
		    &io32->pfrio_nzero, io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRSETTFLAGS:
		if (io32->pfrio_esize != sizeof (struct pfr_table)) {
			error = ENODEV;
			break;
		}
		error = pfr_set_tflags(io32->pfrio_buffer, io32->pfrio_size,
		    io32->pfrio_setflag, io32->pfrio_clrflag,
		    &io32->pfrio_nchange, &io32->pfrio_ndel,
		    io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRCLRADDRS:
		if (io32->pfrio_esize != 0) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_clr_addrs(&io32->pfrio_table, &io32->pfrio_ndel,
		    io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRADDADDRS:
		if (io32->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_add_addrs(&io32->pfrio_table, io32->pfrio_buffer,
		    io32->pfrio_size, &io32->pfrio_nadd, io32->pfrio_flags |
		    PFR_FLAG_USERIOCTL);
		break;

	case DIOCRDELADDRS:
		if (io32->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_del_addrs(&io32->pfrio_table, io32->pfrio_buffer,
		    io32->pfrio_size, &io32->pfrio_ndel, io32->pfrio_flags |
		    PFR_FLAG_USERIOCTL);
		break;

	case DIOCRSETADDRS:
		if (io32->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_set_addrs(&io32->pfrio_table, io32->pfrio_buffer,
		    io32->pfrio_size, &io32->pfrio_size2, &io32->pfrio_nadd,
		    &io32->pfrio_ndel, &io32->pfrio_nchange, io32->pfrio_flags |
		    PFR_FLAG_USERIOCTL, 0);
		break;

	case DIOCRGETADDRS:
		if (io32->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_get_addrs(&io32->pfrio_table, io32->pfrio_buffer,
		    &io32->pfrio_size, io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRGETASTATS:
		if (io32->pfrio_esize != sizeof (struct pfr_astats)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_get_astats(&io32->pfrio_table, io32->pfrio_buffer,
		    &io32->pfrio_size, io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	case DIOCRCLRASTATS:
		if (io32->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_clr_astats(&io32->pfrio_table, io32->pfrio_buffer,
		    io32->pfrio_size, &io32->pfrio_nzero, io32->pfrio_flags |
		    PFR_FLAG_USERIOCTL);
		break;

	case DIOCRTSTADDRS:
		if (io32->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_tst_addrs(&io32->pfrio_table, io32->pfrio_buffer,
		    io32->pfrio_size, &io32->pfrio_nmatch, io32->pfrio_flags |
		    PFR_FLAG_USERIOCTL);
		break;

	case DIOCRINADEFINE:
		if (io32->pfrio_esize != sizeof (struct pfr_addr)) {
			error = ENODEV;
			break;
		}
		pfr_table_copyin_cleanup(&io32->pfrio_table);
		error = pfr_ina_define(&io32->pfrio_table, io32->pfrio_buffer,
		    io32->pfrio_size, &io32->pfrio_nadd, &io32->pfrio_naddr,
		    io32->pfrio_ticket, io32->pfrio_flags | PFR_FLAG_USERIOCTL);
		break;

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

done:
	return (error);
}