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
typedef  int /*<<< orphan*/  AVBSFContext ;

/* Variables and functions */
 int av_bsf_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_list_bsf ; 

int av_bsf_get_null_filter(AVBSFContext **bsf)
{
    return av_bsf_alloc(&ff_list_bsf, bsf);
}