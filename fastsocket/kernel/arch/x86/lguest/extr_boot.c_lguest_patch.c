#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {unsigned int start; unsigned int end; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* lguest_insns ; 
 int /*<<< orphan*/  memcpy (void*,unsigned int,unsigned int) ; 
 int paravirt_patch_default (size_t,int /*<<< orphan*/ ,void*,unsigned long,unsigned int) ; 

__attribute__((used)) static unsigned lguest_patch(u8 type, u16 clobber, void *ibuf,
			     unsigned long addr, unsigned len)
{
	unsigned int insn_len;

	/* Don't do anything special if we don't have a replacement */
	if (type >= ARRAY_SIZE(lguest_insns) || !lguest_insns[type].start)
		return paravirt_patch_default(type, clobber, ibuf, addr, len);

	insn_len = lguest_insns[type].end - lguest_insns[type].start;

	/* Similarly if it can't fit (doesn't happen, but let's be thorough). */
	if (len < insn_len)
		return paravirt_patch_default(type, clobber, ibuf, addr, len);

	/* Copy in our instructions. */
	memcpy(ibuf, lguest_insns[type].start, insn_len);
	return insn_len;
}