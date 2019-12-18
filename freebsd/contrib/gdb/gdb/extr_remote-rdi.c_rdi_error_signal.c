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
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
#define  RDIError_AddressException 165 
#define  RDIError_BadCPUStateSetting 164 
#define  RDIError_BadCoProState 163 
#define  RDIError_BadInstruction 162 
#define  RDIError_BadPointSize 161 
#define  RDIError_BadPointType 160 
#define  RDIError_BigEndian 159 
#define  RDIError_BranchThrough0 158 
#define  RDIError_BreakpointReached 157 
#define  RDIError_DataAbort 156 
#define  RDIError_Error 155 
#define  RDIError_FIQ 154 
#define  RDIError_IRQ 153 
#define  RDIError_IllegalInstruction 152 
#define  RDIError_IncompatibleRDILevels 151 
#define  RDIError_InsufficientPrivilege 150 
#define  RDIError_LittleEndian 149 
#define  RDIError_NoError 148 
#define  RDIError_NoMorePoints 147 
#define  RDIError_NoSuchPoint 146 
#define  RDIError_NotInitialised 145 
#define  RDIError_PrefetchAbort 144 
#define  RDIError_ProgramFinishedInStep 143 
#define  RDIError_Reset 142 
#define  RDIError_SoftInitialiseError 141 
#define  RDIError_SoftwareInterrupt 140 
#define  RDIError_UnableToInitialise 139 
#define  RDIError_UnableToTerminate 138 
#define  RDIError_UndefinedInstruction 137 
#define  RDIError_UndefinedMessage 136 
#define  RDIError_UnimplementedMessage 135 
#define  RDIError_UnimplementedSize 134 
#define  RDIError_UnimplementedType 133 
#define  RDIError_UnknownCoPro 132 
#define  RDIError_UnknownCoProState 131 
#define  RDIError_UserInterrupt 130 
#define  RDIError_WatchpointAccessed 129 
#define  RDIError_WrongByteSex 128 
 int TARGET_SIGNAL_ILL ; 
 int TARGET_SIGNAL_INT ; 
 int TARGET_SIGNAL_SEGV ; 
 int TARGET_SIGNAL_TERM ; 
 int TARGET_SIGNAL_TRAP ; 
 int TARGET_SIGNAL_UNKNOWN ; 

__attribute__((used)) static enum target_signal
rdi_error_signal (int err)
{
  switch (err)
    {
    case RDIError_NoError:
      return 0;
    case RDIError_Reset:
      return TARGET_SIGNAL_TERM;	/* ??? */
    case RDIError_UndefinedInstruction:
      return TARGET_SIGNAL_ILL;
    case RDIError_SoftwareInterrupt:
    case RDIError_PrefetchAbort:
    case RDIError_DataAbort:
      return TARGET_SIGNAL_TRAP;
    case RDIError_AddressException:
      return TARGET_SIGNAL_SEGV;
    case RDIError_IRQ:
    case RDIError_FIQ:
      return TARGET_SIGNAL_TRAP;
    case RDIError_Error:
      return TARGET_SIGNAL_TERM;
    case RDIError_BranchThrough0:
      return TARGET_SIGNAL_TRAP;
    case RDIError_NotInitialised:
    case RDIError_UnableToInitialise:
    case RDIError_WrongByteSex:
    case RDIError_UnableToTerminate:
      return TARGET_SIGNAL_UNKNOWN;
    case RDIError_BadInstruction:
    case RDIError_IllegalInstruction:
      return TARGET_SIGNAL_ILL;
    case RDIError_BadCPUStateSetting:
    case RDIError_UnknownCoPro:
    case RDIError_UnknownCoProState:
    case RDIError_BadCoProState:
    case RDIError_BadPointType:
    case RDIError_UnimplementedType:
    case RDIError_BadPointSize:
    case RDIError_UnimplementedSize:
    case RDIError_NoMorePoints:
      return TARGET_SIGNAL_UNKNOWN;
    case RDIError_BreakpointReached:
    case RDIError_WatchpointAccessed:
      return TARGET_SIGNAL_TRAP;
    case RDIError_NoSuchPoint:
    case RDIError_ProgramFinishedInStep:
      return TARGET_SIGNAL_UNKNOWN;
    case RDIError_UserInterrupt:
      return TARGET_SIGNAL_INT;
    case RDIError_IncompatibleRDILevels:
    case RDIError_LittleEndian:
    case RDIError_BigEndian:
    case RDIError_SoftInitialiseError:
    case RDIError_InsufficientPrivilege:
    case RDIError_UnimplementedMessage:
    case RDIError_UndefinedMessage:
    default:
      return TARGET_SIGNAL_UNKNOWN;
    }
}