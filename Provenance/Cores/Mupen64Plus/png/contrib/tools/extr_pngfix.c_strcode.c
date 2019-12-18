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
#define  INVALID_ERROR_CODE 134 
#define  LIBPNG_ERROR_CODE 133 
#define  LIBPNG_WARNING_CODE 132 
#define  READ_ERROR_CODE 131 
#define  UNEXPECTED_ERROR_CODE 130 
#define  WRITE_ERROR_CODE 129 
#define  ZLIB_ERROR_CODE 128 

__attribute__((used)) static const char *
strcode(int code)
{
   switch (code)
   {
      case LIBPNG_WARNING_CODE:   return "warning";
      case LIBPNG_ERROR_CODE:     return "libpng";
      case ZLIB_ERROR_CODE:       return "zlib";
      case INVALID_ERROR_CODE:    return "invalid";
      case READ_ERROR_CODE:       return "read";
      case WRITE_ERROR_CODE:      return "write";
      case UNEXPECTED_ERROR_CODE: return "unexpected";
      default:                    return "INVALID";
   }
}