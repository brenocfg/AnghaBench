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
typedef  int /*<<< orphan*/  value ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  NATIVE_BYTE_ORDER 129 
#define  SWAP_BYTE_ORDER 128 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int fread (int*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T read_byte_order(FILE *stream, bool *is_native)
{
   uint32_t value;

   if (fread(&value, 1, sizeof(value), stream) != sizeof(value))
      return VC_CONTAINER_ERROR_EOS;

   switch (value)
   {
   case NATIVE_BYTE_ORDER: *is_native = true; break;
   case SWAP_BYTE_ORDER:   *is_native = false; break;
   default: return VC_CONTAINER_ERROR_CORRUPTED;
   }

   return VC_CONTAINER_SUCCESS;
}