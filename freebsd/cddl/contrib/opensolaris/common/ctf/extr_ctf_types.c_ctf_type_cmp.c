#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ctf_id_t ;
struct TYPE_4__ {struct TYPE_4__* ctf_parent; } ;
typedef  TYPE_1__ ctf_file_t ;

/* Variables and functions */
 scalar_t__ CTF_TYPE_ISPARENT (scalar_t__) ; 

int
ctf_type_cmp(ctf_file_t *lfp, ctf_id_t ltype, ctf_file_t *rfp, ctf_id_t rtype)
{
	int rval;

	if (ltype < rtype)
		rval = -1;
	else if (ltype > rtype)
		rval = 1;
	else
		rval = 0;

	if (lfp == rfp)
		return (rval);

	if (CTF_TYPE_ISPARENT(ltype) && lfp->ctf_parent != NULL)
		lfp = lfp->ctf_parent;

	if (CTF_TYPE_ISPARENT(rtype) && rfp->ctf_parent != NULL)
		rfp = rfp->ctf_parent;

	if (lfp < rfp)
		return (-1);

	if (lfp > rfp)
		return (1);

	return (rval);
}