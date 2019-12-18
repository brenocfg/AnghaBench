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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BITS_READ_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  bits_0_to_10 ; 
 int /*<<< orphan*/  countof (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_read_u32(void)
{
   VC_CONTAINER_BITS_T bit_stream;
   uint32_t ii, value;
   int error_count = 0;

   LOG_DEBUG(NULL, "Testing vc_container_bits_get_u32");
   BITS_INIT(NULL, &bit_stream, bits_0_to_10, countof(bits_0_to_10));

   for (ii = 0; ii < 11; ii++)
   {
      value = BITS_READ_U32(NULL, &bit_stream, ii, "test_read_u32");
      if (value != ii)
      {
         LOG_ERROR(NULL, "Expected %u, got %u", ii, value);
         error_count++;
      }
   }

   value = BITS_READ_U32(NULL, &bit_stream, 1, "Final bit");
   if (!BITS_VALID(NULL, &bit_stream) || value)
   {
      LOG_ERROR(NULL, "Failed to get final bit");
      error_count++;
   }
   value = BITS_READ_U32(NULL, &bit_stream, 1, "Beyond final bit");
   if (BITS_VALID(NULL, &bit_stream) || value)
   {
      LOG_ERROR(NULL, "Unexpectedly succeeded reading beyond expected end of stream");
      error_count++;
   }

   return error_count;
}