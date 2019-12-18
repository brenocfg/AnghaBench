#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  int ulong_t ;
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_5__ {scalar_t__ pa_addr; int /*<<< orphan*/ * pa_file; } ;
typedef  TYPE_1__ dt_printarg_t ;
struct TYPE_6__ {unsigned long long cte_bits; } ;
typedef  TYPE_2__ ctf_encoding_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NBBY ; 
 int /*<<< orphan*/  bcopy (scalar_t__,int*,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_bitfield(dt_printarg_t *pap, ulong_t off, ctf_encoding_t *ep)
{
	FILE *fp = pap->pa_file;
	caddr_t addr = pap->pa_addr + off / NBBY;
	uint64_t mask = (1ULL << ep->cte_bits) - 1;
	uint64_t value = 0;
	size_t size = (ep->cte_bits + (NBBY - 1)) / NBBY;
	uint8_t *buf = (uint8_t *)&value;
	uint8_t shift;

	/*
	 * On big-endian machines, we need to adjust the buf pointer to refer
	 * to the lowest 'size' bytes in 'value', and we need to shift based on
	 * the offset from the end of the data, not the offset of the start.
	 */
#if BYTE_ORDER == _BIG_ENDIAN
	buf += sizeof (value) - size;
	off += ep->cte_bits;
#endif
	bcopy(addr, buf, size);
	shift = off % NBBY;

	/*
	 * Offsets are counted from opposite ends on little- and
	 * big-endian machines.
	 */
#if BYTE_ORDER == _BIG_ENDIAN
	shift = NBBY - shift;
#endif

	/*
	 * If the bits we want do not begin on a byte boundary, shift the data
	 * right so that the value is in the lowest 'cte_bits' of 'value'.
	 */
	if (off % NBBY != 0)
		value >>= shift;
	value &= mask;

	(void) fprintf(fp, "%#llx", (u_longlong_t)value);
}