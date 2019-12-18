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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ RNC_FILE_IS_NOT_RNC ; 
 scalar_t__ RNC_SIGNATURE ; 
 scalar_t__ blong (unsigned char*) ; 

s32 depackrnc1_ulen(void *packed)
{
    unsigned char *p = packed;
    if (blong (p) != RNC_SIGNATURE)
	return RNC_FILE_IS_NOT_RNC;
    return blong (p+4);
}