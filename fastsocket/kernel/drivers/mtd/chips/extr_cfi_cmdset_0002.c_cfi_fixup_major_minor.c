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
struct cfi_private {scalar_t__ mfr; int id; } ;
struct cfi_pri_amdstd {char MajorVersion; } ;

/* Variables and functions */
 scalar_t__ CFI_MFR_SAMSUNG ; 

__attribute__((used)) static void cfi_fixup_major_minor(struct cfi_private *cfi,
				  struct cfi_pri_amdstd *extp)
{
	if (cfi->mfr == CFI_MFR_SAMSUNG && cfi->id == 0x257e &&
	    extp->MajorVersion == '0')
		extp->MajorVersion = '1';
}