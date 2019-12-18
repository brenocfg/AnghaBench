#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pe_cmd; int pe_flags; TYPE_1__* pe_ch; } ;
struct TYPE_6__ {scalar_t__ ch_optsize; } ;
typedef  TYPE_1__ PE_CoffHdr ;
typedef  TYPE_2__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int LIBPE_F_DIRTY_COFF_HEADER ; 
 int LIBPE_F_DIRTY_OPT_HEADER ; 
 int LIBPE_F_FD_DONE ; 
 scalar_t__ PE_C_READ ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* malloc (int) ; 

int
pe_update_coff_header(PE *pe, PE_CoffHdr *ch)
{

	if (pe == NULL || ch == NULL) {
		errno = EINVAL;
		return (-1);
	}

	if (pe->pe_cmd == PE_C_READ || pe->pe_flags & LIBPE_F_FD_DONE) {
		errno = EACCES;
		return (-1);
	}

	if (pe->pe_ch == NULL) {
		if ((pe->pe_ch = malloc(sizeof(PE_CoffHdr))) == NULL) {
			errno = ENOMEM;
			return (-1);
		}
	} else {
		/* Rewrite optional header if `optsize' field changed. */
		if (pe->pe_ch->ch_optsize != ch->ch_optsize)
			pe->pe_flags |= LIBPE_F_DIRTY_OPT_HEADER;
	}

	*pe->pe_ch = *ch;

	pe->pe_flags |= LIBPE_F_DIRTY_COFF_HEADER;

	return (0);
}