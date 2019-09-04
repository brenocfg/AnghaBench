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
typedef  scalar_t__ U_32 ;
struct TYPE_3__ {int platformErrorCode; scalar_t__ errorMessageBufferSize; char* errorMessageBuffer; int /*<<< orphan*/  portableErrorCode; } ;
typedef  TYPE_1__* PortlibPTBuffers_t ;
typedef  int /*<<< orphan*/  I_32 ;

/* Variables and functions */
 scalar_t__ HYERROR_DEFAULT_BUFFER_SIZE ; 
 char* XMLVM_ATOMIC_MALLOC (scalar_t__) ; 
 int /*<<< orphan*/  XMLVM_FREE (char*) ; 
 TYPE_1__* hyport_tls_get () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

I_32 hyerror_set_last_error_with_message (I_32 portableCode, const char *errorMessage)
{
    PortlibPTBuffers_t ptBuffers;
    U_32 requiredSize;
    
    /* get the buffers, allocate if necessary.
     * Silently return if not present, what else would the caller do anyway? 
     */
    ptBuffers = hyport_tls_get ();
    if (NULL == ptBuffers)
    {
        return portableCode;
    }
    
    /* Save the last error */
    ptBuffers->platformErrorCode = -1;
    ptBuffers->portableErrorCode = portableCode;
    
    /* Store the message, allocate a bigger buffer if required.  Keep the old buffer around
     * just in case memory can not be allocated
     */
    requiredSize = strlen (errorMessage) + 1;
    requiredSize =
    requiredSize <
    HYERROR_DEFAULT_BUFFER_SIZE ? HYERROR_DEFAULT_BUFFER_SIZE : requiredSize;
    if (requiredSize > ptBuffers->errorMessageBufferSize)
    {
        char *newBuffer = XMLVM_ATOMIC_MALLOC(requiredSize);
        if (NULL != newBuffer)
        {
            if (ptBuffers->errorMessageBuffer != NULL)
            {
                XMLVM_FREE(ptBuffers->errorMessageBuffer);
            }
            ptBuffers->errorMessageBuffer = newBuffer;
            ptBuffers->errorMessageBufferSize = requiredSize;
        }
    }
    
    /* Save the message */
    if (ptBuffers->errorMessageBufferSize > 0)
    {
        sprintf(ptBuffers->errorMessageBuffer, "%s", errorMessage);
        ptBuffers->errorMessageBuffer[ptBuffers->errorMessageBufferSize - 1] = '\0';
    }
    
    return portableCode;
}