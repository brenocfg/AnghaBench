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
typedef  int /*<<< orphan*/  tdata_t ;
typedef  int /*<<< orphan*/  iiburst_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int CTF_COMPRESS ; 
 int CTF_FUZZY_MATCH ; 
 int CTF_SWAP_BYTES ; 
 int CTF_USE_DYNSYM ; 
 int /*<<< orphan*/  ctf_gen (int /*<<< orphan*/ *,size_t*,int) ; 
 int /*<<< orphan*/  iiburst_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sort_iidescs (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static caddr_t
make_ctf_data(tdata_t *td, Elf *elf, const char *file, size_t *lenp, int flags)
{
	iiburst_t *iiburst;
	caddr_t data;

	iiburst = sort_iidescs(elf, file, td, flags & CTF_FUZZY_MATCH,
	    flags & CTF_USE_DYNSYM);
	data = ctf_gen(iiburst, lenp, flags & (CTF_COMPRESS |  CTF_SWAP_BYTES));

	iiburst_free(iiburst);

	return (data);
}