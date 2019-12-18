#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int /*<<< orphan*/  ctf_lblent_t ;
struct TYPE_7__ {int cth_lbloff; int cth_objtoff; } ;
typedef  TYPE_2__ ctf_header_t ;
struct TYPE_6__ {scalar_t__ cts_data; } ;
struct TYPE_8__ {scalar_t__ ctf_version; int ctf_buf; TYPE_1__ ctf_data; } ;
typedef  TYPE_3__ ctf_file_t ;

/* Variables and functions */
 scalar_t__ CTF_VERSION_2 ; 
 int /*<<< orphan*/  ECTF_NOTSUP ; 
 int ctf_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
extract_label_info(ctf_file_t *fp, const ctf_lblent_t **ctl, uint_t *num_labels)
{
	const ctf_header_t *h;

	/*
	 * Labels are only supported in V2 or later
	 */
	if (fp->ctf_version < CTF_VERSION_2)
		return (ctf_set_errno(fp, ECTF_NOTSUP));

	h = (const ctf_header_t *)fp->ctf_data.cts_data;

	/* LINTED - pointer alignment */
	*ctl = (const ctf_lblent_t *)(fp->ctf_buf + h->cth_lbloff);
	*num_labels = (h->cth_objtoff - h->cth_lbloff) / sizeof (ctf_lblent_t);

	return (0);
}