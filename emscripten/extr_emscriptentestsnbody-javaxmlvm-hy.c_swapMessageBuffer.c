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
struct TYPE_3__ {char* reportedMessageBuffer; scalar_t__ reportedMessageBufferSize; char const* errorMessageBuffer; scalar_t__ errorMessageBufferSize; scalar_t__ portableErrorCode; scalar_t__ reportedErrorCode; } ;
typedef  TYPE_1__* PortlibPTBuffers_t ;

/* Variables and functions */

__attribute__((used)) static const char* swapMessageBuffer (PortlibPTBuffers_t ptBuffers, const char *message)
{
    char *tempBuffer = ptBuffers->reportedMessageBuffer;
    U_32 tempBufferSize = ptBuffers->reportedMessageBufferSize;
    
    if (message == NULL)
    {
        return "";
    }
    
    /* Can't swap unknown message buffer */
    if (message != ptBuffers->errorMessageBuffer)
    {
        return message;
    }
    
    /* Save reported information */
    ptBuffers->reportedErrorCode = ptBuffers->portableErrorCode;
    ptBuffers->reportedMessageBuffer = ptBuffers->errorMessageBuffer;
    ptBuffers->reportedMessageBufferSize = ptBuffers->errorMessageBufferSize;
    
    if (tempBufferSize > 0)
    {
        tempBuffer[0] = '\0';
    }
    
    /* Clear pending fields ready for next error */
    ptBuffers->portableErrorCode = 0;
    ptBuffers->errorMessageBuffer = tempBuffer;
    ptBuffers->errorMessageBufferSize = tempBufferSize;
    
    return ptBuffers->reportedMessageBuffer;
}