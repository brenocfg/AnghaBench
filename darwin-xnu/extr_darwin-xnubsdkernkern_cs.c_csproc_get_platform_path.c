#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct proc {int dummy; } ;
struct cs_blob {int csb_platform_path; } ;

/* Variables and functions */
 struct cs_blob* csproc_get_blob (struct proc*) ; 

int
csproc_get_platform_path(struct proc *p)
{
	struct cs_blob *csblob;

    csblob = csproc_get_blob(p);

	return (csblob == NULL) ? 0 : csblob->csb_platform_path;
}