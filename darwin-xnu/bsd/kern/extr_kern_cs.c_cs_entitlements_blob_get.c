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
struct cs_blob {int dummy; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int p_csflags; int /*<<< orphan*/  p_textoff; int /*<<< orphan*/ * p_textvp; } ;

/* Variables and functions */
 int CS_SIGNED ; 
 int EINVAL ; 
 int csblob_get_entitlements (struct cs_blob*,void**,size_t*) ; 
 struct cs_blob* ubc_cs_blob_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
cs_entitlements_blob_get(proc_t p, void **out_start, size_t *out_length)
{
	struct cs_blob *csblob;

	*out_start = NULL;
	*out_length = 0;

	if ((p->p_csflags & CS_SIGNED) == 0) {
		return 0;
	}

	if (NULL == p->p_textvp)
		return EINVAL;

	if ((csblob = ubc_cs_blob_get(p->p_textvp, -1, p->p_textoff)) == NULL)
		return 0;

	return csblob_get_entitlements(csblob, out_start, out_length);
}