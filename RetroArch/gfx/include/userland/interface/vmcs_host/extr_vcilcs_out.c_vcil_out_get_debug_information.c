#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  exe ;
struct TYPE_6__ {int /*<<< orphan*/  ilcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  OMX_STRING ;
typedef  int /*<<< orphan*/  OMX_S32 ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ IL_GET_DEBUG_INFORMATION_EXECUTE_T ;
typedef  TYPE_2__ ILCS_COMMON_T ;

/* Variables and functions */
 int /*<<< orphan*/  IL_GET_DEBUG_INFORMATION ; 
 int /*<<< orphan*/  OMX_ErrorHardware ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 scalar_t__ ilcs_execute_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int*) ; 

OMX_ERRORTYPE vcil_out_get_debug_information(ILCS_COMMON_T *st, OMX_STRING debugInfo, OMX_S32 *pLen)
{
   IL_GET_DEBUG_INFORMATION_EXECUTE_T exe;

   exe.len = *pLen;

   if(ilcs_execute_function(st->ilcs, IL_GET_DEBUG_INFORMATION, &exe, sizeof(exe), debugInfo, (int *) pLen) < 0)
      return OMX_ErrorHardware;

   return OMX_ErrorNone;
}