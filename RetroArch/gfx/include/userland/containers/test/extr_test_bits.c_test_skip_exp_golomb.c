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
 int /*<<< orphan*/  BITS_SKIP_EXP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  countof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exp_golomb_0_to_10 ; 

__attribute__((used)) static int test_skip_exp_golomb(void)
{
   VC_CONTAINER_BITS_T bit_stream;
   uint32_t ii;
   int error_count = 0;

   LOG_DEBUG(NULL, "Testing vc_container_bits_skip_exp_golomb");
   BITS_INIT(NULL, &bit_stream, exp_golomb_0_to_10, countof(exp_golomb_0_to_10));

   for (ii = 0; ii < 12; ii++)
   {
      BITS_SKIP_EXP(NULL, &bit_stream, "test_skip_exp_golomb");
   }

   if (!BITS_VALID(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Failed to skip through buffer");
      error_count++;
   }

   BITS_SKIP_EXP(NULL, &bit_stream, "Skip beyond end of stream");
   if (BITS_VALID(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Unexpectedly succeeded skipping beyond expected end of stream");
      error_count++;
   }

   return error_count;
}