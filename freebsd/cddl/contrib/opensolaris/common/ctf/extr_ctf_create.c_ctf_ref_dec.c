#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_6__ {int ctf_flags; } ;
typedef  TYPE_1__ ctf_file_t ;
struct TYPE_7__ {int dtd_ref; } ;
typedef  TYPE_2__ ctf_dtdef_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int LCTF_RDWR ; 
 TYPE_2__* ctf_dtd_lookup (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctf_ref_dec(ctf_file_t *fp, ctf_id_t tid)
{
	ctf_dtdef_t *dtd = ctf_dtd_lookup(fp, tid);

	if (dtd == NULL)
		return;

	if (!(fp->ctf_flags & LCTF_RDWR))
		return;

	ASSERT(dtd->dtd_ref >= 1);
	dtd->dtd_ref--;
}