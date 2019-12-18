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
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  int /*<<< orphan*/  tACL_CONN ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_API (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * btm_bda_to_acl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOLEAN BTM_IsAclConnectionUp (BD_ADDR remote_bda, tBT_TRANSPORT transport)
{
    tACL_CONN   *p;

    BTM_TRACE_API ("BTM_IsAclConnectionUp: RemBdAddr: %02x%02x%02x%02x%02x%02x\n",
                   remote_bda[0], remote_bda[1], remote_bda[2],
                   remote_bda[3], remote_bda[4], remote_bda[5]);

    p = btm_bda_to_acl(remote_bda, transport);
    if (p != (tACL_CONN *)NULL) {
        return (TRUE);
    }

    /* If here, no BD Addr found */
    return (FALSE);
}