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
typedef  size_t ulong_t ;
struct TYPE_6__ {int ctf_dthashlen; int /*<<< orphan*/  ctf_dtdefs; TYPE_2__** ctf_dthash; } ;
typedef  TYPE_1__ ctf_file_t ;
struct TYPE_7__ {int dtd_type; struct TYPE_7__* dtd_hash; } ;
typedef  TYPE_2__ ctf_dtdef_t ;

/* Variables and functions */
 int /*<<< orphan*/  ctf_list_append (int /*<<< orphan*/ *,TYPE_2__*) ; 

void
ctf_dtd_insert(ctf_file_t *fp, ctf_dtdef_t *dtd)
{
	ulong_t h = dtd->dtd_type & (fp->ctf_dthashlen - 1);

	dtd->dtd_hash = fp->ctf_dthash[h];
	fp->ctf_dthash[h] = dtd;
	ctf_list_append(&fp->ctf_dtdefs, dtd);
}