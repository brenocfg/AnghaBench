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
typedef  int ALenum ;

/* Variables and functions */
#define  ALUT_ERROR_ALC_ERROR_ON_ENTRY 146 
#define  ALUT_ERROR_AL_ERROR_ON_ENTRY 145 
#define  ALUT_ERROR_BUFFER_DATA 144 
#define  ALUT_ERROR_CLOSE_DEVICE 143 
#define  ALUT_ERROR_CORRUPT_OR_TRUNCATED_DATA 142 
#define  ALUT_ERROR_CREATE_CONTEXT 141 
#define  ALUT_ERROR_DESTROY_CONTEXT 140 
#define  ALUT_ERROR_GEN_BUFFERS 139 
#define  ALUT_ERROR_INVALID_ENUM 138 
#define  ALUT_ERROR_INVALID_OPERATION 137 
#define  ALUT_ERROR_INVALID_VALUE 136 
#define  ALUT_ERROR_IO_ERROR 135 
#define  ALUT_ERROR_MAKE_CONTEXT_CURRENT 134 
#define  ALUT_ERROR_NO_CURRENT_CONTEXT 133 
#define  ALUT_ERROR_NO_ERROR 132 
#define  ALUT_ERROR_OPEN_DEVICE 131 
#define  ALUT_ERROR_OUT_OF_MEMORY 130 
#define  ALUT_ERROR_UNSUPPORTED_FILE_SUBTYPE 129 
#define  ALUT_ERROR_UNSUPPORTED_FILE_TYPE 128 

const char *alutGetErrorString(ALenum error)
{
  switch (error)
  {
  case ALUT_ERROR_NO_ERROR:
    return "No ALUT error found";

  case ALUT_ERROR_OUT_OF_MEMORY:
    return "ALUT ran out of memory";

  case ALUT_ERROR_INVALID_ENUM:
    return "ALUT was given an invalid enumeration token";

  case ALUT_ERROR_INVALID_VALUE:
    return "ALUT was given an invalid value";

  case ALUT_ERROR_INVALID_OPERATION:
    return "The operation was invalid in the current ALUT state";

  case ALUT_ERROR_NO_CURRENT_CONTEXT:
    return "There is no current AL context";

  case ALUT_ERROR_AL_ERROR_ON_ENTRY:
    return "There was already an AL error on entry to an ALUT function";

  case ALUT_ERROR_ALC_ERROR_ON_ENTRY:
    return "There was already an ALC error on entry to an ALUT function";

  case ALUT_ERROR_OPEN_DEVICE:
    return "There was an error opening the ALC device";

  case ALUT_ERROR_CLOSE_DEVICE:
    return "There was an error closing the ALC device";

  case ALUT_ERROR_CREATE_CONTEXT:
    return "There was an error creating an ALC context";

  case ALUT_ERROR_MAKE_CONTEXT_CURRENT:
    return "Could not change the current ALC context";

  case ALUT_ERROR_DESTROY_CONTEXT:
    return "There was an error destroying the ALC context";

  case ALUT_ERROR_GEN_BUFFERS:
    return "There was an error generating an AL buffer";

  case ALUT_ERROR_BUFFER_DATA:
    return "There was an error passing buffer data to AL";

  case ALUT_ERROR_IO_ERROR:
    return "I/O error";

  case ALUT_ERROR_UNSUPPORTED_FILE_TYPE:
    return "Unsupported file type";

  case ALUT_ERROR_UNSUPPORTED_FILE_SUBTYPE:
    return "Unsupported mode within an otherwise usable file type";

  case ALUT_ERROR_CORRUPT_OR_TRUNCATED_DATA:
    return "The sound data was corrupt or truncated";

  default:
    return "An impossible ALUT error condition was reported?!?";
  }
}