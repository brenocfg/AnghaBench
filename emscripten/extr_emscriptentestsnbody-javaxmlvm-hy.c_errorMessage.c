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
struct TYPE_3__ {int errorMessageBufferSize; char* errorMessageBuffer; } ;
typedef  TYPE_1__* PortlibPTBuffers_t ;
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 int HYERROR_DEFAULT_BUFFER_SIZE ; 
 char* XMLVM_ATOMIC_MALLOC (int) ; 
 TYPE_1__* hyport_tls_peek () ; 
 int /*<<< orphan*/  strerror_r (int /*<<< orphan*/ ,char*,int) ; 

const char* errorMessage (I_32 errorCode)
{
    PortlibPTBuffers_t ptBuffers;
    
    ptBuffers = hyport_tls_peek ();
    if (0 == ptBuffers->errorMessageBufferSize)
    {
        ptBuffers->errorMessageBuffer = XMLVM_ATOMIC_MALLOC(HYERROR_DEFAULT_BUFFER_SIZE);
        if (NULL == ptBuffers->errorMessageBuffer)
        {
            return "";
        }
        ptBuffers->errorMessageBufferSize = HYERROR_DEFAULT_BUFFER_SIZE;
    }
    
    /* Copy from OS to ptBuffers */
#if !defined(ZOS)
    strerror_r(errorCode,
               ptBuffers->errorMessageBuffer, ptBuffers->errorMessageBufferSize);
#else
    /* Do not have strerror_r on z/OS so use port library function instead */
    portLibrary->str_printf(portLibrary, ptBuffers->errorMessageBuffer, ptBuffers->errorMessageBufferSize, strerror(errorCode));
#endif /* ZOS */
    ptBuffers->errorMessageBuffer[ptBuffers->errorMessageBufferSize - 1] = '\0';
    return ptBuffers->errorMessageBuffer;
}