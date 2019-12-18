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

/* Variables and functions */
 int /*<<< orphan*/  CDVD_FLUSHCACHE ; 
 int /*<<< orphan*/  SifCallRpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd0 ; 
 int /*<<< orphan*/  cdvd_inited ; 
 int /*<<< orphan*/ * sbuff ; 

void CDVD_FlushCache()
{
    if (!cdvd_inited)
        return;

    SifCallRpc(&cd0, CDVD_FLUSHCACHE, 0, (void *)(&sbuff[0]), 0, (void *)(&sbuff[0]), 0, 0, 0);

    return;
}