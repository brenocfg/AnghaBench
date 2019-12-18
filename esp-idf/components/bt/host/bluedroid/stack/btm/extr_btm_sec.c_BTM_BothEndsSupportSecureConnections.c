#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ (* supports_secure_connections ) () ;} ;
typedef  int BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTM_PeerSupportsSecureConnections (int /*<<< orphan*/ ) ; 
 TYPE_1__* controller_get_interface () ; 
 scalar_t__ stub1 () ; 

BOOLEAN BTM_BothEndsSupportSecureConnections(BD_ADDR bd_addr)
{
    return ((controller_get_interface()->supports_secure_connections()) &&
            (BTM_PeerSupportsSecureConnections(bd_addr)));
}