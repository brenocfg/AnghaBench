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
typedef  int /*<<< orphan*/  VC_MEM_ADDR_T ;
typedef  int /*<<< orphan*/  VC_MEM_ACCESS_HANDLE_T ;

/* Variables and functions */
 int AccessVideoCoreMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  WRITE_MEM ; 

int WriteVideoCoreMemory( VC_MEM_ACCESS_HANDLE_T vcHandle,
                          void *buf,
                          VC_MEM_ADDR_T vcMemAddr,
                          size_t numBytes )
{
    return AccessVideoCoreMemory( vcHandle, WRITE_MEM, buf, vcMemAddr, numBytes );
}