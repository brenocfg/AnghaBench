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
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  LookupVideoCoreSymbol (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  ReadVideoCoreMemory (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 

int ReadVideoCoreStringBySymbol( VC_MEM_ACCESS_HANDLE_T vcHandle,
                                 const char *symbol,
                                 char *buf,
                                 size_t bufSize )
{
    VC_MEM_ADDR_T   vcMemAddr;
    size_t          vcMemSize;

    if ( !LookupVideoCoreSymbol( vcHandle, symbol, &vcMemAddr, &vcMemSize ))
    {
        ERR( "Symbol not found: '%s'", symbol );
        return 0;
    }

    if ( vcMemSize > bufSize )
    {
        vcMemSize = bufSize;
    }

    if ( !ReadVideoCoreMemory( vcHandle, buf, vcMemAddr, vcMemSize ))
    {
        ERR( "Unable to read %zu bytes @ 0x%08x", vcMemSize, vcMemAddr );
        return 0;
    }

    // Make sure that the result is null-terminated

    buf[vcMemSize-1] = '\0';
    return 1;
}