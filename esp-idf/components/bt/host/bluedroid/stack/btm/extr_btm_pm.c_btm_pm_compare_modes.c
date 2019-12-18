#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mode; int /*<<< orphan*/  timeout; int /*<<< orphan*/  attempt; int /*<<< orphan*/  min; int /*<<< orphan*/  max; } ;
typedef  TYPE_1__ tBTM_PM_PWR_MD ;
typedef  size_t UINT8 ;

/* Variables and functions */
#define  BTM_PM_GET_COMP 130 
#define  BTM_PM_GET_MD1 129 
#define  BTM_PM_GET_MD2 128 
 int BTM_PM_MD_ACTIVE ; 
 int BTM_PM_MD_FORCE ; 
 int BTM_PM_MD_SNIFF ; 
 int BTM_PM_NUM_SET_MODES ; 
 size_t* btm_pm_md_comp_matrix ; 

__attribute__((used)) static tBTM_PM_PWR_MD *btm_pm_compare_modes(tBTM_PM_PWR_MD *p_md1, tBTM_PM_PWR_MD *p_md2, tBTM_PM_PWR_MD *p_res)
{
    UINT8 res;

    if (p_md1 == NULL) {
        *p_res = *p_md2;
        p_res->mode &= ~BTM_PM_MD_FORCE;

        return p_md2;
    }

    if (p_md2->mode == BTM_PM_MD_ACTIVE || p_md1->mode == BTM_PM_MD_ACTIVE) {
        return NULL;
    }

    /* check if force bit is involved */
    if (p_md1->mode & BTM_PM_MD_FORCE) {
        *p_res = *p_md1;
        p_res->mode &= ~BTM_PM_MD_FORCE;
        return p_res;
    }

    if (p_md2->mode & BTM_PM_MD_FORCE) {
        *p_res = *p_md2;
        p_res->mode &= ~BTM_PM_MD_FORCE;
        return p_res;
    }

    res = (p_md1->mode - 1) * BTM_PM_NUM_SET_MODES + (p_md2->mode - 1);
    res = btm_pm_md_comp_matrix[res];
    switch (res) {
    case BTM_PM_GET_MD1:
        *p_res = *p_md1;
        return p_md1;

    case BTM_PM_GET_MD2:
        *p_res = *p_md2;
        return p_md2;

    case BTM_PM_GET_COMP:
        p_res->mode = p_md1->mode;
        /* min of the two */
        p_res->max  = (p_md1->max < p_md2->max) ? (p_md1->max) : (p_md2->max);
        /* max of the two */
        p_res->min  = (p_md1->min > p_md2->min) ? (p_md1->min) : (p_md2->min);

        /* the intersection is NULL */
        if ( p_res->max < p_res->min) {
            return NULL;
        }

        if (p_res->mode == BTM_PM_MD_SNIFF) {
            /* max of the two */
            p_res->attempt  = (p_md1->attempt > p_md2->attempt) ? (p_md1->attempt) : (p_md2->attempt);
            p_res->timeout  = (p_md1->timeout > p_md2->timeout) ? (p_md1->timeout) : (p_md2->timeout);
        }
        return p_res;
    }
    return NULL;
}