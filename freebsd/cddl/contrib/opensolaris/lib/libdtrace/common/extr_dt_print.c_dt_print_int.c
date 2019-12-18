#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ulong_t ;
struct TYPE_8__ {scalar_t__ pa_addr; int /*<<< orphan*/ * pa_ctfp; int /*<<< orphan*/ * pa_file; } ;
typedef  TYPE_1__ dt_printarg_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_9__ {int cte_format; size_t cte_bits; } ;
typedef  TYPE_2__ ctf_encoding_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 int CTF_INT_VARARGS ; 
 scalar_t__ CTF_IS_CHAR (TYPE_2__) ; 
 size_t NBBY ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dt_print_hex (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ isprint (char) ; 
 int /*<<< orphan*/  print_bitfield (TYPE_1__*,size_t,TYPE_2__*) ; 

__attribute__((used)) static void
dt_print_int(ctf_id_t base, ulong_t off, dt_printarg_t *pap)
{
	FILE *fp = pap->pa_file;
	ctf_file_t *ctfp = pap->pa_ctfp;
	ctf_encoding_t e;
	size_t size;
	caddr_t addr = pap->pa_addr + off / NBBY;

	if (ctf_type_encoding(ctfp, base, &e) == CTF_ERR) {
		(void) fprintf(fp, "<unknown encoding>");
		return;
	}

	/*
	 * This comes from MDB - it's not clear under what circumstances this
	 * would be found.
	 */
	if (e.cte_format & CTF_INT_VARARGS) {
		(void) fprintf(fp, "...");
		return;
	}

	/*
	 * We print this as a bitfield if the bit encoding indicates it's not
	 * an even power of two byte size, or is larger than 8 bytes.
	 */
	size = e.cte_bits / NBBY;
	if (size > 8 || (e.cte_bits % NBBY) != 0 || (size & (size - 1)) != 0) {
		print_bitfield(pap, off, &e);
		return;
	}

	/*
	 * If this is a character, print it out as such.
	 */
	if (CTF_IS_CHAR(e)) {
		char c = *(char *)addr;
		if (isprint(c))
			(void) fprintf(fp, "'%c'", c);
		else if (c == 0)
			(void) fprintf(fp, "'\\0'");
		else
			(void) fprintf(fp, "'\\%03o'", c);
		return;
	}

	dt_print_hex(fp, addr, size);
}