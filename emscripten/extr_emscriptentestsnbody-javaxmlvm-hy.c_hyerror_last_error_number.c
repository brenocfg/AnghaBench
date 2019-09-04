#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ portableErrorCode; scalar_t__ reportedErrorCode; } ;
typedef  TYPE_1__* PortlibPTBuffers_t ;
typedef  scalar_t__ I_32 ;

/* Variables and functions */
 TYPE_1__* hyport_tls_peek () ; 

I_32 hyerror_last_error_number ()
{
    PortlibPTBuffers_t ptBuffers;
    
    /* get the buffers, return failure if not present */
    ptBuffers = hyport_tls_peek ();
    if (NULL == ptBuffers)
    {
        return 0;
    }
    
    /* New error ? */
    if (ptBuffers->portableErrorCode != 0)
    {
        return ptBuffers->portableErrorCode;
    }
    else
    {
        return ptBuffers->reportedErrorCode;
    }
}