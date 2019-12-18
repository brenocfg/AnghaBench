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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tccb_tcat {int dummy; } ;
struct tccb_tcah {int dummy; } ;
struct TYPE_2__ {int tcal; } ;
struct tccb {TYPE_1__ tcah; int /*<<< orphan*/ * tca; } ;
struct dcw {int /*<<< orphan*/ * cd; void* cd_count; int /*<<< orphan*/  count; void* flags; void* cmd; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENOSPC ; 
 struct dcw* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  memset (struct dcw*,int /*<<< orphan*/ ,int) ; 
 int tca_size (struct tccb*) ; 

struct dcw *tccb_add_dcw(struct tccb *tccb, size_t tccb_size, u8 cmd, u8 flags,
			 void *cd, u8 cd_count, u32 count)
{
	struct dcw *dcw;
	int size;
	int tca_offset;

	/* Check for space. */
	tca_offset = tca_size(tccb);
	size = ALIGN(sizeof(struct dcw) + cd_count, 4);
	if (sizeof(struct tccb_tcah) + tca_offset + size +
	    sizeof(struct tccb_tcat) > tccb_size)
		return ERR_PTR(-ENOSPC);
	/* Add dcw to tca. */
	dcw = (struct dcw *) &tccb->tca[tca_offset];
	memset(dcw, 0, size);
	dcw->cmd = cmd;
	dcw->flags = flags;
	dcw->count = count;
	dcw->cd_count = cd_count;
	if (cd)
		memcpy(&dcw->cd[0], cd, cd_count);
	tccb->tcah.tcal += size;
	return dcw;
}