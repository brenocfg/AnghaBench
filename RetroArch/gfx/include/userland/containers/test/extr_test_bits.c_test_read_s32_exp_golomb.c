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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BITS_READ_S32_EXP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  countof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exp_golomb_0_to_10 ; 
 int /*<<< orphan*/  exp_golomb_large ; 
 int /*<<< orphan*/  exp_golomb_oversize ; 
 int* exp_golomb_values ; 

__attribute__((used)) static int test_read_s32_exp_golomb(void)
{
   VC_CONTAINER_BITS_T bit_stream;
   uint32_t ii;
   int32_t value;
   int error_count = 0;

   LOG_DEBUG(NULL, "Testing vc_container_bits_get_s32_exp_golomb");
   BITS_INIT(NULL, &bit_stream, exp_golomb_0_to_10, countof(exp_golomb_0_to_10));

   for (ii = 0; ii < 11; ii++)
   {
      value = BITS_READ_S32_EXP(NULL, &bit_stream, "test_read_s32_exp_golomb");
      if (value != exp_golomb_values[ii])
      {
         LOG_ERROR(NULL, "Expected %u, got %u", ii, value);
         error_count++;
      }
   }

   value = BITS_READ_S32_EXP(NULL, &bit_stream, "Final bit");
   if (!BITS_VALID(NULL, &bit_stream) || value)
   {
      LOG_ERROR(NULL, "Failed to get final Exp-Golomb value (expected a zero)");
      error_count++;
   }
   value = BITS_READ_S32_EXP(NULL, &bit_stream, "Beyond final bit");
   if (BITS_VALID(NULL, &bit_stream) || value)
   {
      LOG_ERROR(NULL, "Unexpectedly succeeded reading beyond expected end of stream");
      error_count++;
   }

   /* Test getting two large (32 bit) Exp-Golomb values */
   BITS_INIT(NULL, &bit_stream, exp_golomb_large, countof(exp_golomb_large));

   value = BITS_READ_S32_EXP(NULL, &bit_stream, "Largest signed 32-bit value");
   if (!BITS_VALID(NULL, &bit_stream) || value != -0x7FFFFFFF)
   {
      LOG_ERROR(NULL, "Failed to get largest signed 32-bit value: %d", value);
      error_count++;
   }

   value = BITS_READ_S32_EXP(NULL, &bit_stream, "Just too large signed 33-bit value");
   if (BITS_VALID(NULL, &bit_stream) || value)
   {
      LOG_ERROR(NULL, "Unexpectedly got slightly too large signed 32-bit value: %d", value);
      error_count++;
   }

   /* Test getting an oversize (33 bit) Exp-Golomb value */
   BITS_INIT(NULL, &bit_stream, exp_golomb_oversize, countof(exp_golomb_oversize));

   value = BITS_READ_S32_EXP(NULL, &bit_stream, "Larger signed 33-bit value");
   if (BITS_VALID(NULL, &bit_stream) || value)
   {
      LOG_ERROR(NULL, "Unexpectedly got signed 33-bit value: %d", value);
      error_count++;
   }

   return error_count;
}