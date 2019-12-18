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
typedef  int /*<<< orphan*/  tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/ * btm_find_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * btm_sec_alloc_dev (int /*<<< orphan*/ ) ; 

tBTM_SEC_DEV_REC *btm_find_or_alloc_dev (BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    BTM_TRACE_EVENT ("btm_find_or_alloc_dev\n");
    if ((p_dev_rec = btm_find_dev (bd_addr)) == NULL) {

        /* Allocate a new device record or reuse the oldest one */
        p_dev_rec = btm_sec_alloc_dev (bd_addr);
    }
    return (p_dev_rec);
}