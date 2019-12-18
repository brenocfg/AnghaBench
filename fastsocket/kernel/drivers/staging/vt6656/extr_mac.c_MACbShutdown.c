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
typedef  int /*<<< orphan*/  PSDevice ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLnsRequestOutAsyn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MESSAGE_TYPE_MACSHUTDOWN ; 
 int /*<<< orphan*/  TRUE ; 

BOOL MACbShutdown (PSDevice pDevice)
{
    CONTROLnsRequestOutAsyn(pDevice,
                        MESSAGE_TYPE_MACSHUTDOWN,
                        0,
                        0,
                        0,
                        NULL
                        );
    return TRUE;
}