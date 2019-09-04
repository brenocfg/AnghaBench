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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  hashOffset; int /*<<< orphan*/  nSpecialSlots; } ;
typedef  TYPE_1__ CS_CodeDirectory ;

/* Variables and functions */
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const uint8_t *
find_special_slot(const CS_CodeDirectory *cd, size_t slotsize, uint32_t slot)
{
	/* there is no zero special slot since that is the first code slot */
	if (ntohl(cd->nSpecialSlots) < slot || slot == 0)
		return NULL;

	return ((const uint8_t *)cd + ntohl(cd->hashOffset) - (slotsize * slot));
}