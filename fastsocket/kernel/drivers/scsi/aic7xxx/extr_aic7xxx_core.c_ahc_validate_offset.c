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
typedef  scalar_t__ u_int ;
struct ahc_syncrate {int dummy; } ;
struct ahc_softc {int features; } ;
struct TYPE_4__ {scalar_t__ offset; } ;
struct TYPE_3__ {scalar_t__ offset; } ;
struct ahc_initiator_tinfo {TYPE_2__ goal; TYPE_1__ user; } ;
typedef  scalar_t__ role_t ;

/* Variables and functions */
 int AHC_ULTRA2 ; 
 scalar_t__ MAX_OFFSET_16BIT ; 
 scalar_t__ MAX_OFFSET_8BIT ; 
 scalar_t__ MAX_OFFSET_ULTRA2 ; 
 scalar_t__ ROLE_TARGET ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ahc_validate_offset(struct ahc_softc *ahc,
		    struct ahc_initiator_tinfo *tinfo,
		    const struct ahc_syncrate *syncrate,
		    u_int *offset, int wide, role_t role)
{
	u_int maxoffset;

	/* Limit offset to what we can do */
	if (syncrate == NULL) {
		maxoffset = 0;
	} else if ((ahc->features & AHC_ULTRA2) != 0) {
		maxoffset = MAX_OFFSET_ULTRA2;
	} else {
		if (wide)
			maxoffset = MAX_OFFSET_16BIT;
		else
			maxoffset = MAX_OFFSET_8BIT;
	}
	*offset = min(*offset, maxoffset);
	if (tinfo != NULL) {
		if (role == ROLE_TARGET)
			*offset = min(*offset, (u_int)tinfo->user.offset);
		else
			*offset = min(*offset, (u_int)tinfo->goal.offset);
	}
}