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
 int BITS_AVAILABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BITS_SKIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  bits_0_to_10 ; 
 int /*<<< orphan*/  countof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plural_ext (int) ; 

__attribute__((used)) static int test_skip(void)
{
   VC_CONTAINER_BITS_T bit_stream;
   uint32_t ii;
   int error_count = 0;
   uint32_t last_bits_left, bits_left;

   LOG_DEBUG(NULL, "Testing vc_container_bits_skip");
   BITS_INIT(NULL, &bit_stream, bits_0_to_10, countof(bits_0_to_10));

   last_bits_left = BITS_AVAILABLE(NULL, &bit_stream);
   for (ii = 0; ii < 11; ii++)
   {
      BITS_SKIP(NULL, &bit_stream, ii, "test_skip");
      bits_left = BITS_AVAILABLE(NULL, &bit_stream);
      if (bits_left + ii != last_bits_left)
      {
         int32_t actual = last_bits_left - bits_left;
         LOG_ERROR(NULL, "Tried to skip %u bit%s, actually skipped %d bit%s",
               ii, plural_ext(ii), actual, plural_ext(actual));
         error_count++;
      }
      last_bits_left = bits_left;
   }

   BITS_SKIP(NULL, &bit_stream, 1, "Final bit");
   if (!BITS_VALID(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Failed to skip final bit");
      error_count++;
   }
   if (BITS_AVAILABLE(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "End of stream not reached by skipping");
      error_count++;
   }

   BITS_SKIP(NULL, &bit_stream, 1, "Beyond final bit");
   if (BITS_VALID(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Unexpectedly succeeded skipping beyond expected end of stream");
      error_count++;
   }
   return error_count;
}