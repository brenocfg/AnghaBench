#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong_t ;
struct TYPE_8__ {int ctl_typeidx; int /*<<< orphan*/  ctl_label; } ;
typedef  TYPE_1__ ctf_lblent_t ;
struct TYPE_9__ {int cth_lbloff; int cth_objtoff; } ;
typedef  TYPE_2__ ctf_header_t ;
struct TYPE_10__ {int cd_ctflen; scalar_t__ cd_ctfdata; } ;
typedef  TYPE_3__ ctf_data_t ;

/* Variables and functions */
 int E_SUCCESS ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  print_line (char*) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 char* ref_to_str (int /*<<< orphan*/ ,TYPE_2__ const*,TYPE_3__ const*) ; 

__attribute__((used)) static int
print_labeltable(const ctf_header_t *hp, const ctf_data_t *cd)
{
	void *v = (void *) (cd->cd_ctfdata + hp->cth_lbloff);
	const ctf_lblent_t *ctl = v;
	ulong_t i, n = (hp->cth_objtoff - hp->cth_lbloff) / sizeof (*ctl);

	print_line("- Label Table ");

	if (hp->cth_lbloff & 3)
		WARN("cth_lbloff is not aligned properly\n");
	if (hp->cth_lbloff >= cd->cd_ctflen)
		WARN("file is truncated or cth_lbloff is corrupt\n");
	if (hp->cth_objtoff >= cd->cd_ctflen)
		WARN("file is truncated or cth_objtoff is corrupt\n");
	if (hp->cth_lbloff > hp->cth_objtoff)
		WARN("file is corrupt -- cth_lbloff > cth_objtoff\n");

	for (i = 0; i < n; i++, ctl++) {
		(void) printf("  %5u %s\n", ctl->ctl_typeidx,
		    ref_to_str(ctl->ctl_label, hp, cd));
	}

	return (E_SUCCESS);
}