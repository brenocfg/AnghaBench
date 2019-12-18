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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;

/* Variables and functions */
 scalar_t__ BITS_AVAILABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BITS_BYTES_AVAILABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BITS_CURRENT_POINTER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BITS_REDUCE_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,char*) ; 
 scalar_t__ BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ bits_0_to_10 ; 
 scalar_t__ countof (scalar_t__) ; 
 int /*<<< orphan*/  plural_ext (scalar_t__) ; 

__attribute__((used)) static int test_reduce_bytes(void)
{
   VC_CONTAINER_BITS_T bit_stream;
   uint32_t ii;
   int error_count = 0;
   uint32_t last_bytes_left, bytes_left;

   LOG_DEBUG(NULL, "Testing vc_container_bits_reduce_bytes");
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

   for (ii = 0; ii < 4; ii++)
   {
      BITS_REDUCE_BYTES(NULL, &bit_stream, ii, "test_reduce_bytes");

      if (BITS_CURRENT_POINTER(NULL, &bit_stream) != bits_0_to_10)
      {
         LOG_ERROR(NULL, "Did not expect current pointer to have moved");
         error_count++;
      }

      bytes_left = BITS_BYTES_AVAILABLE(NULL, &bit_stream);
      if (bytes_left + ii != last_bytes_left)
      {
         int32_t actual = last_bytes_left - bytes_left;
         LOG_ERROR(NULL, "Tried to reduce by %u byte%s, actually reduced by %d byte%s",
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

   BITS_REDUCE_BYTES(NULL, &bit_stream, bytes_left + 1, "Reducing an empty stream");
   if (BITS_VALID(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Unexpectedly succeeded reducing by too many bytes");
      error_count++;
   }
   if (BITS_AVAILABLE(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Expected stream to have been reset");
      error_count++;
   }

   return error_count;
}