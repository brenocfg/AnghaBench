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
struct TYPE_3__ {scalar_t__ errorMessageBufferSize; char* errorMessageBuffer; void* portableErrorCode; void* platformErrorCode; } ;
typedef  TYPE_1__* PortlibPTBuffers_t ;
typedef  void* I_32 ;

/* Variables and functions */
 TYPE_1__* hyport_tls_get () ; 

I_32 hyerror_set_last_error (I_32 platformCode, I_32 portableCode)
{
    PortlibPTBuffers_t ptBuffers;
    
    /* get the buffers, allocate if necessary.
     * Silently return if not present, what else would the caller do anyway? 
     */
    ptBuffers = hyport_tls_get ();
    if (NULL == ptBuffers)
    {
        return portableCode;
    }
    
    /* Save the last error */
    ptBuffers->platformErrorCode = platformCode;
    ptBuffers->portableErrorCode = portableCode;
    
    /* Overwrite any customized messages stored */
    if (ptBuffers->errorMessageBufferSize > 0)
    {
        ptBuffers->errorMessageBuffer[0] = '\0';
    }
    
    return portableCode;
}