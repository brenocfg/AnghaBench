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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 int TTM_PL_FLAG_CACHED ; 
 int TTM_PL_FLAG_UNCACHED ; 
 int TTM_PL_FLAG_WC ; 
 int /*<<< orphan*/  _PAGE_GUARDED ; 
 int /*<<< orphan*/  _PAGE_NO_CACHE ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 

pgprot_t ttm_io_prot(uint32_t caching_flags, pgprot_t tmp)
{
#if defined(__i386__) || defined(__x86_64__)
	if (caching_flags & TTM_PL_FLAG_WC)
		tmp = pgprot_writecombine(tmp);
	else if (boot_cpu_data.x86 > 3)
		tmp = pgprot_noncached(tmp);

#elif defined(__powerpc__)
	if (!(caching_flags & TTM_PL_FLAG_CACHED)) {
		pgprot_val(tmp) |= _PAGE_NO_CACHE;
		if (caching_flags & TTM_PL_FLAG_UNCACHED)
			pgprot_val(tmp) |= _PAGE_GUARDED;
	}
#endif
#if defined(__ia64__)
	if (caching_flags & TTM_PL_FLAG_WC)
		tmp = pgprot_writecombine(tmp);
	else
		tmp = pgprot_noncached(tmp);
#endif
#if defined(__sparc__) || defined(__mips__)
	if (!(caching_flags & TTM_PL_FLAG_CACHED))
		tmp = pgprot_noncached(tmp);
#endif
	return tmp;
}