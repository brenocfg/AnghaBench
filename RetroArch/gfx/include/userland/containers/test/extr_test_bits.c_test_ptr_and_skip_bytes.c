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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;

/* Variables and functions */
 scalar_t__ BITS_BYTES_AVAILABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BITS_CURRENT_POINTER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  BITS_SKIP_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char*) ; 
 scalar_t__ BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  const* bits_0_to_10 ; 
 scalar_t__ countof (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  plural_ext (scalar_t__) ; 

__attribute__((used)) static int test_ptr_and_skip_bytes(void)
{
   VC_CONTAINER_BITS_T bit_stream;
   uint32_t ii;
   const uint8_t *expected_ptr;
   int error_count = 0;
   uint32_t last_bytes_left, bytes_left;

   LOG_DEBUG(NULL, "Testing vc_container_bits_current_pointer, vc_container_bits_skip_bytes and vc_container_bits_bytes_available");
   BITS_INIT(NULL, &bit_stream, bits_0_to_10, countof(bits_0_to_10));

   last_bytes_left = BITS_BYTES_AVAILABLE(NULL, &bit_stream);
   if (last_bytes_left != countof(bits_0_to_10))
   {
      LOG_ERROR(NULL, "Expected bytes available to initially match given size");
      error_count++;
   }

   if (BITS_CURRENT_POINTER(NULL, &bit_stream) != bits_0_to_10)
   {
      LOG_ERROR(NULL, "Expected initial current pointer to match original buffer");
      error_count++;
   }

   expected_ptr = bits_0_to_10;
   for (ii = 0; ii < 4; ii++)
   {
      BITS_SKIP_BYTES(NULL, &bit_stream, ii, "test_ptr_and_skip_bytes");

      expected_ptr += ii;
      if (BITS_CURRENT_POINTER(NULL, &bit_stream) != expected_ptr)
      {
         LOG_ERROR(NULL, "Expected current pointer to have moved by %u byte%s", ii, plural_ext(ii));
         error_count++;
      }

      bytes_left = BITS_BYTES_AVAILABLE(NULL, &bit_stream);
      if (bytes_left + ii != last_bytes_left)
      {
         int32_t actual = last_bytes_left - bytes_left;
         LOG_ERROR(NULL, "Tried to skip %u byte%s, actually skipped %d byte%s",
               ii, plural_ext(ii), actual, plural_ext(actual));
         error_count++;
      }

      last_bytes_left = bytes_left;
   }

   if (!bytes_left)
   {
      LOG_ERROR(NULL, "Reached end of stream too soon");
      error_count++;
   }
   if (!BITS_VALID(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Expected stream to be valid");
      error_count++;
   }

   BITS_SKIP_BYTES(NULL, &bit_stream, bytes_left + 1, "Beyond end of stream");
   if (BITS_VALID(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Unexpectedly succeeded skipping bytes beyond end of stream");
      error_count++;
   }
   if (BITS_BYTES_AVAILABLE(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Expected stream to have been reset");
      error_count++;
   }

   return error_count;
}