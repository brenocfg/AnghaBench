#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ulong_t ;
typedef  int ctf_id_t ;
struct TYPE_5__ {int ctf_dthashlen; TYPE_2__** ctf_dthash; } ;
typedef  TYPE_1__ ctf_file_t ;
struct TYPE_6__ {int dtd_type; struct TYPE_6__* dtd_hash; } ;
typedef  TYPE_2__ ctf_dtdef_t ;

/* Variables and functions */

ctf_dtdef_t *
ctf_dtd_lookup(ctf_file_t *fp, ctf_id_t type)
{
	ulong_t h = type & (fp->ctf_dthashlen - 1);
	ctf_dtdef_t *dtd;

	if (fp->ctf_dthash == NULL)
		return (NULL);

	for (dtd = fp->ctf_dthash[h]; dtd != NULL; dtd = dtd->dtd_hash) {
		if (dtd->dtd_type == type)
			break;
	}

	return (dtd);
}