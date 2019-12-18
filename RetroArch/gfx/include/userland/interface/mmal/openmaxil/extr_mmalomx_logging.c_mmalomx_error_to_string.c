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
typedef  scalar_t__ OMX_ERRORTYPE ;

/* Variables and functions */
 size_t MMALOMX_SAT (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ OMX_ErrorInsufficientResources ; 
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ vcos_countof (char const**) ; 

const char *mmalomx_error_to_string(OMX_ERRORTYPE error)
{
  static const char *names[] = {
    "OMX_ErrorInsufficientResources", "OMX_ErrorUndefined",
    "OMX_ErrorInvalidComponentName", "OMX_ErrorComponentNotFound",
    "OMX_ErrorInvalidComponent", "OMX_ErrorBadParameter",
    "OMX_ErrorNotImplemented", "OMX_ErrorUnderflow",
    "OMX_ErrorOverflow", "OMX_ErrorHardware", "OMX_ErrorInvalidState",
    "OMX_ErrorStreamCorrupt", "OMX_ErrorPortsNotCompatible",
    "OMX_ErrorResourcesLost", "OMX_ErrorNoMore", "OMX_ErrorVersionMismatch",
    "OMX_ErrorNotReady", "OMX_ErrorTimeout", "OMX_ErrorSameState",
    "OMX_ErrorResourcesPreempted", "OMX_ErrorPortUnresponsiveDuringAllocation",
    "OMX_ErrorPortUnresponsiveDuringDeallocation",
    "OMX_ErrorPortUnresponsiveDuringStop", "OMX_ErrorIncorrectStateTransition",
    "OMX_ErrorIncorrectStateOperation", "OMX_ErrorUnsupportedSetting",
    "OMX_ErrorUnsupportedIndex", "OMX_ErrorBadPortIndex",
    "OMX_ErrorPortUnpopulated", "OMX_ErrorComponentSuspended",
    "OMX_ErrorDynamicResourcesUnavailable", "OMX_ErrorMbErrorsInFrame",
    "OMX_ErrorFormatNotDetected", "OMX_ErrorContentPipeOpenFailed",
    "OMX_ErrorContentPipeCreationFailed", "OMX_ErrorSeperateTablesUsed",
    "OMX_ErrorTunnelingUnsupported",
    "OMX_Error unknown"
  };

  if(error == OMX_ErrorNone) return "OMX_ErrorNone";

  error -= OMX_ErrorInsufficientResources;
  return names[MMALOMX_SAT((int)error, 0, (int)vcos_countof(names)-1)];
}