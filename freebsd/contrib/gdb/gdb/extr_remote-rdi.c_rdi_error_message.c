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

/* Variables and functions */
#define  RDIError_AddressException 166 
#define  RDIError_BadCPUStateSetting 165 
#define  RDIError_BadCoProState 164 
#define  RDIError_BadInstruction 163 
#define  RDIError_BadPointSize 162 
#define  RDIError_BadPointType 161 
#define  RDIError_BigEndian 160 
#define  RDIError_BranchThrough0 159 
#define  RDIError_BreakpointReached 158 
#define  RDIError_CantSetPoint 157 
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

__attribute__((used)) static char *
rdi_error_message (int err)
{
  switch (err)
    {
    case RDIError_NoError:
      return "no error";
    case RDIError_Reset:
      return "debuggee reset";
    case RDIError_UndefinedInstruction:
      return "undefined instruction";
    case RDIError_SoftwareInterrupt:
      return "SWI trapped";
    case RDIError_PrefetchAbort:
      return "prefetch abort, execution ran into unmapped memory?";
    case RDIError_DataAbort:
      return "data abort, no memory at specified address?";
    case RDIError_AddressException:
      return "address exception, access >26bit in 26bit mode";
    case RDIError_IRQ:
      return "IRQ, interrupt trapped";
    case RDIError_FIQ:
      return "FIQ, fast interrupt trapped";
    case RDIError_Error:
      return "a miscellaneous type of error";
    case RDIError_BranchThrough0:
      return "branch through location 0";
    case RDIError_NotInitialised:
      return "internal error, RDI_open not called first";
    case RDIError_UnableToInitialise:
      return "internal error, target world is broken";
    case RDIError_WrongByteSex:
      return "See Operator: WrongByteSex";
    case RDIError_UnableToTerminate:
      return "See Operator: Unable to Terminate";
    case RDIError_BadInstruction:
      return "bad instruction, illegal to execute this instruction";
    case RDIError_IllegalInstruction:
      return "illegal instruction, the effect of executing it is undefined";
    case RDIError_BadCPUStateSetting:
      return "internal error, tried to set SPSR of user mode";
    case RDIError_UnknownCoPro:
      return "unknown co-processor";
    case RDIError_UnknownCoProState:
      return "cannot execute co-processor request";
    case RDIError_BadCoProState:
      return "recognizably broken co-processor request";
    case RDIError_BadPointType:
      return "internal error, bad point yype";
    case RDIError_UnimplementedType:
      return "internal error, unimplemented type";
    case RDIError_BadPointSize:
      return "internal error, bad point size";
    case RDIError_UnimplementedSize:
      return "internal error, unimplemented size";
    case RDIError_NoMorePoints:
      return "last break/watch point was used";
    case RDIError_BreakpointReached:
      return "breakpoint reached";
    case RDIError_WatchpointAccessed:
      return "watchpoint accessed";
    case RDIError_NoSuchPoint:
      return "attempted to clear non-existent break/watch point";
    case RDIError_ProgramFinishedInStep:
      return "end of the program reached while stepping";
    case RDIError_UserInterrupt:
      return "you pressed Escape";
    case RDIError_CantSetPoint:
      return "no more break/watch points available";
    case RDIError_IncompatibleRDILevels:
      return "incompatible RDI levels";
    case RDIError_LittleEndian:
      return "debuggee is little endian";
    case RDIError_BigEndian:
      return "debuggee is big endian";
    case RDIError_SoftInitialiseError:
      return "recoverable error in RDI initialization";
    case RDIError_InsufficientPrivilege:
      return "internal error, supervisor state not accessible to monitor";
    case RDIError_UnimplementedMessage:
      return "internal error, unimplemented message";
    case RDIError_UndefinedMessage:
      return "internal error, undefined message";
    default:
      return "undefined error message, should reset target";
    }
}