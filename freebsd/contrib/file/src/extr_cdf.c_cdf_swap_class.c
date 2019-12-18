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
struct TYPE_3__ {void** cl_word; int /*<<< orphan*/  cl_dword; } ;
typedef  TYPE_1__ cdf_classid_t ;

/* Variables and functions */
 void* CDF_TOLE2 (void*) ; 
 int /*<<< orphan*/  CDF_TOLE4 (int /*<<< orphan*/ ) ; 

void
cdf_swap_class(cdf_classid_t *d)
{
	d->cl_dword = CDF_TOLE4(d->cl_dword);
	d->cl_word[0] = CDF_TOLE2(d->cl_word[0]);
	d->cl_word[1] = CDF_TOLE2(d->cl_word[1]);
}