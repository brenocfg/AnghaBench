#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ portableErrorCode; scalar_t__ errorMessageBufferSize; char* errorMessageBuffer; scalar_t__ reportedMessageBufferSize; char* reportedMessageBuffer; int /*<<< orphan*/  platformErrorCode; } ;
typedef  TYPE_1__* PortlibPTBuffers_t ;

/* Variables and functions */
 char* errorMessage (int /*<<< orphan*/ ) ; 
 TYPE_1__* hyport_tls_peek () ; 
 char const* swapMessageBuffer (TYPE_1__*,char const*) ; 

const char* hyerror_last_error_message ()
{
    PortlibPTBuffers_t ptBuffers;
    
    /* Was an error saved ? */
    ptBuffers = hyport_tls_peek ();
    if (NULL == ptBuffers)
    {
        return "";
    }
    
    /* New error ? */
    if (ptBuffers->portableErrorCode != 0)
    {
        const char *message = NULL;
        
        /* Customized message stored ? */
        if (ptBuffers->errorMessageBufferSize > 0)
        {
            if ('\0' != ptBuffers->errorMessageBuffer[0])
            {
                message = ptBuffers->errorMessageBuffer;
            }
        }
        
        /* Call a helper to get the last message from the OS.  */
        if (message == NULL)
        {
            message = errorMessage (ptBuffers->platformErrorCode);
        }
        
        /* Avoid overwrite by internal portlib errors */
        return swapMessageBuffer (ptBuffers, message);
    }
    
    /* Previous message stored ? */
    if (ptBuffers->reportedMessageBufferSize > 0)
    {
        if ('\0' != ptBuffers->reportedMessageBuffer[0])
        {
            return ptBuffers->reportedMessageBuffer;
        }
    }
    
    /* No error.  */
    return "";
}