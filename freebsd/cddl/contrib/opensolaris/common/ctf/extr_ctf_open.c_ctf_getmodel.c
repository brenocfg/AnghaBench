#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ctf_dmodel; } ;
typedef  TYPE_2__ ctf_file_t ;
struct TYPE_4__ {int ctd_code; } ;

/* Variables and functions */

int
ctf_getmodel(ctf_file_t *fp)
{
	return (fp->ctf_dmodel->ctd_code);
}