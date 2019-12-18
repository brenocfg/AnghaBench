#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct cs_hash {size_t cs_size; } ;
typedef  int /*<<< orphan*/  scatter ;
struct TYPE_5__ {scalar_t__ pageSize; size_t hashSize; scalar_t__ teamOffset; scalar_t__ version; scalar_t__ identOffset; scalar_t__ nCodeSlots; scalar_t__ scatterOffset; scalar_t__ hashOffset; scalar_t__ nSpecialSlots; int /*<<< orphan*/  hashType; scalar_t__ magic; } ;
struct TYPE_4__ {scalar_t__ count; } ;
typedef  TYPE_1__ SC_Scatter ;
typedef  TYPE_2__ CS_CodeDirectory ;

/* Variables and functions */
 size_t CSMAGIC_CODEDIRECTORY ; 
 size_t CS_SUPPORTSSCATTER ; 
 size_t CS_SUPPORTSTEAMID ; 
 int EBADEXEC ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PAGE_SHIFT_4K ; 
 struct cs_hash* cs_find_md (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 size_t ntohl (scalar_t__) ; 

__attribute__((used)) static int
cs_validate_codedirectory(const CS_CodeDirectory *cd, size_t length)
{
	struct cs_hash const *hashtype;

	if (length < sizeof(*cd))
		return EBADEXEC;
	if (ntohl(cd->magic) != CSMAGIC_CODEDIRECTORY)
		return EBADEXEC;
	if (cd->pageSize < PAGE_SHIFT_4K || cd->pageSize > PAGE_SHIFT)
		return EBADEXEC;
	hashtype = cs_find_md(cd->hashType);
	if (hashtype == NULL)
		return EBADEXEC;

	if (cd->hashSize != hashtype->cs_size)
		return EBADEXEC;

	if (length < ntohl(cd->hashOffset))
		return EBADEXEC;

	/* check that nSpecialSlots fits in the buffer in front of hashOffset */
	if (ntohl(cd->hashOffset) / hashtype->cs_size < ntohl(cd->nSpecialSlots))
		return EBADEXEC;

	/* check that codeslots fits in the buffer */
	if ((length - ntohl(cd->hashOffset)) / hashtype->cs_size <  ntohl(cd->nCodeSlots))
		return EBADEXEC;
	
	if (ntohl(cd->version) >= CS_SUPPORTSSCATTER && cd->scatterOffset) {

		if (length < ntohl(cd->scatterOffset))
			return EBADEXEC;

		const SC_Scatter *scatter = (const SC_Scatter *)
			(((const uint8_t *)cd) + ntohl(cd->scatterOffset));
		uint32_t nPages = 0;

		/*
		 * Check each scatter buffer, since we don't know the
		 * length of the scatter buffer array, we have to
		 * check each entry.
		 */
		while(1) {
			/* check that the end of each scatter buffer in within the length */
			if (((const uint8_t *)scatter) + sizeof(scatter[0]) > (const uint8_t *)cd + length)
				return EBADEXEC;
			uint32_t scount = ntohl(scatter->count);
			if (scount == 0)
				break;
			if (nPages + scount < nPages)
				return EBADEXEC;
			nPages += scount;
			scatter++;

			/* XXX check that basees doesn't overlap */
			/* XXX check that targetOffset doesn't overlap */
		}
#if 0 /* rdar://12579439 */
		if (nPages != ntohl(cd->nCodeSlots))
			return EBADEXEC;
#endif
	}

	if (length < ntohl(cd->identOffset))
		return EBADEXEC;

	/* identifier is NUL terminated string */
	if (cd->identOffset) {
		const uint8_t *ptr = (const uint8_t *)cd + ntohl(cd->identOffset);
		if (memchr(ptr, 0, length - ntohl(cd->identOffset)) == NULL)
			return EBADEXEC;
	}

	/* team identifier is NULL terminated string */
	if (ntohl(cd->version) >= CS_SUPPORTSTEAMID && ntohl(cd->teamOffset)) {
		if (length < ntohl(cd->teamOffset))
			return EBADEXEC;

		const uint8_t *ptr = (const uint8_t *)cd + ntohl(cd->teamOffset);
		if (memchr(ptr, 0, length - ntohl(cd->teamOffset)) == NULL)
			return EBADEXEC;
	}

	return 0;
}