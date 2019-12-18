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
typedef  int /*<<< orphan*/  patch_t ;

/* Variables and functions */
 int /*<<< orphan*/  PU_STATIC ; 
 scalar_t__ W_CacheLumpName (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sttminus ; 

void STlib_init(void)
{
    sttminus = (patch_t *) W_CacheLumpName("STTMINUS", PU_STATIC);
}