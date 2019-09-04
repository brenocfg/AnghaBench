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
typedef  int /*<<< orphan*/  HEVCContext ;

/* Variables and functions */
 int GET_CABAC (int /*<<< orphan*/ ) ; 
 size_t SAO_MERGE_FLAG ; 
 int /*<<< orphan*/ * elem_offset ; 

int ff_hevc_sao_merge_flag_decode(HEVCContext *s)
{
    return GET_CABAC(elem_offset[SAO_MERGE_FLAG]);
}