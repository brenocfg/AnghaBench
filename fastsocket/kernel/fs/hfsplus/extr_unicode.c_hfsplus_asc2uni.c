#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
typedef  scalar_t__ u16 ;
struct super_block {int dummy; } ;
struct hfsplus_unistr {void* length; void** unicode; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 scalar_t__ HFSPLUS_MAX_STRLEN ; 
 TYPE_1__ HFSPLUS_SB (struct super_block*) ; 
 int HFSPLUS_SB_NODECOMPOSE ; 
 int asc2unichar (struct super_block*,char const*,int,scalar_t__*) ; 
 void* cpu_to_be16 (scalar_t__) ; 
 scalar_t__* decompose_unichar (scalar_t__,int*) ; 

int hfsplus_asc2uni(struct super_block *sb, struct hfsplus_unistr *ustr,
		    const char *astr, int len)
{
	int size, dsize, decompose;
	u16 *dstr, outlen = 0;
	wchar_t c;

	decompose = !(HFSPLUS_SB(sb).flags & HFSPLUS_SB_NODECOMPOSE);
	while (outlen < HFSPLUS_MAX_STRLEN && len > 0) {
		size = asc2unichar(sb, astr, len, &c);

		if (decompose && (dstr = decompose_unichar(c, &dsize))) {
			if (outlen + dsize > HFSPLUS_MAX_STRLEN)
				break;
			do {
				ustr->unicode[outlen++] = cpu_to_be16(*dstr++);
			} while (--dsize > 0);
		} else
			ustr->unicode[outlen++] = cpu_to_be16(c);

		astr += size;
		len -= size;
	}
	ustr->length = cpu_to_be16(outlen);
	if (len > 0)
		return -ENAMETOOLONG;
	return 0;
}