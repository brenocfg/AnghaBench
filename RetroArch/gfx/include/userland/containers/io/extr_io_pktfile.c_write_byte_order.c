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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  NATIVE_BYTE_ORDER ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_SPACE ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T write_byte_order(FILE *stream)
{
   /* Simple byte order header word */
   uint32_t value = NATIVE_BYTE_ORDER;

   if (fwrite(&value, 1, sizeof(value), stream) != sizeof(value))
      return VC_CONTAINER_ERROR_OUT_OF_SPACE;

   return VC_CONTAINER_SUCCESS;
}