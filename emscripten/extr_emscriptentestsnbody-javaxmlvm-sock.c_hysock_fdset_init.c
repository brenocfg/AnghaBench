#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hyfdset_struct {int dummy; } ;
typedef  int /*<<< orphan*/  hysocket_t ;
typedef  TYPE_1__* hyfdset_t ;
struct TYPE_7__ {TYPE_1__* fdset; } ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__* PortlibPTBuffers_t ;
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HYPORT_ERROR_SOCKET_SYSTEMFULL ; 
 int /*<<< orphan*/  SOCKET_CAST (int /*<<< orphan*/ ) ; 
 TYPE_1__* XMLVM_ATOMIC_MALLOC (int) ; 
 TYPE_2__* hyport_tls_get () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

I_32 hysock_fdset_init (hysocket_t socketP)
{
    PortlibPTBuffers_t ptBuffers;
    hyfdset_t fdset;
    
    ptBuffers = hyport_tls_get ();
    if (NULL == ptBuffers)
    {
        return HYPORT_ERROR_SOCKET_SYSTEMFULL;
    }
    
    if (NULL == ptBuffers->fdset)
    {
        ptBuffers->fdset = XMLVM_ATOMIC_MALLOC(sizeof (struct hyfdset_struct));
        
        if (NULL == ptBuffers->fdset)
        {
            return HYPORT_ERROR_SOCKET_SYSTEMFULL;
        }
    }
    fdset = ptBuffers->fdset;
    memset (fdset, 0, sizeof (struct hyfdset_struct));
    
    FD_ZERO (&fdset->handle);
    FD_SET (SOCKET_CAST (socketP), &fdset->handle);
    return 0;
}