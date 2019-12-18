#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  exe ;
struct TYPE_9__ {int /*<<< orphan*/  ilcs; } ;
struct TYPE_8__ {int index; } ;
struct TYPE_7__ {int /*<<< orphan*/  err; scalar_t__ name; } ;
typedef  int OMX_U32 ;
typedef  scalar_t__* OMX_STRING ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ IL_COMPONENT_NAME_ENUM_RESPONSE_T ;
typedef  TYPE_2__ IL_COMPONENT_NAME_ENUM_EXECUTE_T ;
typedef  TYPE_3__ ILCS_COMMON_T ;

/* Variables and functions */
 int /*<<< orphan*/  IL_COMPONENT_NAME_ENUM ; 
 int /*<<< orphan*/  OMX_ErrorHardware ; 
 scalar_t__ ilcs_execute_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

OMX_ERRORTYPE vcil_out_component_name_enum(ILCS_COMMON_T *st, OMX_STRING cComponentName, OMX_U32 nNameLength, OMX_U32 nIndex)
{
   IL_COMPONENT_NAME_ENUM_EXECUTE_T exe;
   IL_COMPONENT_NAME_ENUM_RESPONSE_T resp;
   int rlen = sizeof(resp);

   exe.index = nIndex;

   if(ilcs_execute_function(st->ilcs, IL_COMPONENT_NAME_ENUM, &exe, sizeof(exe), &resp, &rlen) < 0 || rlen != sizeof(resp))
      return OMX_ErrorHardware;

   if (sizeof(resp.name) < nNameLength)
      nNameLength = sizeof(resp.name);

   strncpy((char *)cComponentName, (char *) resp.name, nNameLength);
   cComponentName[127] = 0;
   return resp.err;
}