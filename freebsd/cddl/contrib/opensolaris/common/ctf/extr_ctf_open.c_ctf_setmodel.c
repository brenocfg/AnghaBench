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
struct TYPE_6__ {TYPE_2__ const* ctf_dmodel; } ;
typedef  TYPE_1__ ctf_file_t ;
struct TYPE_7__ {int ctd_code; int /*<<< orphan*/ * ctd_name; } ;
typedef  TYPE_2__ ctf_dmodel_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 TYPE_2__* _libctf_models ; 
 int ctf_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
ctf_setmodel(ctf_file_t *fp, int model)
{
	const ctf_dmodel_t *dp;

	for (dp = _libctf_models; dp->ctd_name != NULL; dp++) {
		if (dp->ctd_code == model) {
			fp->ctf_dmodel = dp;
			return (0);
		}
	}

	return (ctf_set_errno(fp, EINVAL));
}