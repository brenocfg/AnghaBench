#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct cs_blob {int csb_hash_pageshift; TYPE_2__* csb_cd; int /*<<< orphan*/ * csb_teamid; int /*<<< orphan*/  csb_platform_binary; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  codeLimit; int /*<<< orphan*/  scatterOffset; int /*<<< orphan*/  version; int /*<<< orphan*/  nCodeSlots; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ SC_Scatter ;
typedef  TYPE_2__ CS_CodeDirectory ;

/* Variables and functions */
 int CS_SUPPORTSSCATTER ; 
 int /*<<< orphan*/  FALSE ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TRUE ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
ubc_cs_supports_multilevel_hash(struct cs_blob *blob)
{
	const CS_CodeDirectory *cd;

	
	/*
	 * Only applies to binaries that ship as part of the OS,
	 * primarily the shared cache.
	 */
	if (!blob->csb_platform_binary || blob->csb_teamid != NULL) {
		return FALSE;
	}

	/*
	 * If the runtime page size matches the code signing page
	 * size, there is no work to do.
	 */
	if (PAGE_SHIFT <= blob->csb_hash_pageshift) {
		return FALSE;
	}

	cd = blob->csb_cd;

	/*
	 * There must be a valid integral multiple of hashes
	 */
	if (ntohl(cd->nCodeSlots) & (PAGE_MASK >> blob->csb_hash_pageshift)) {
		return FALSE;
	}

	/*
	 * Scatter lists must also have ranges that have an integral number of hashes
	 */
	if ((ntohl(cd->version) >= CS_SUPPORTSSCATTER) && (ntohl(cd->scatterOffset))) {

		const SC_Scatter *scatter = (const SC_Scatter*)
			((const char*)cd + ntohl(cd->scatterOffset));
		/* iterate all scatter structs to make sure they are all aligned */
		do {
			uint32_t sbase = ntohl(scatter->base);
			uint32_t scount = ntohl(scatter->count);

			/* last scatter? */
			if (scount == 0) {
				break;
			}

			if (sbase & (PAGE_MASK >> blob->csb_hash_pageshift)) {
				return FALSE;
			}

			if (scount & (PAGE_MASK >> blob->csb_hash_pageshift)) {
				return FALSE;
			}

			scatter++;
		} while(1);
	}

	/* Covered range must be a multiple of the new page size */
	if (ntohl(cd->codeLimit) & PAGE_MASK) {
		return FALSE;
	}

	/* All checks pass */
	return TRUE;
}