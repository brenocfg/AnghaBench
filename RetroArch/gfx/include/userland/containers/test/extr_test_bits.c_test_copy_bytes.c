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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_COPY_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BITS_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BITS_REDUCE_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  BITS_SKIP_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * bits_0_to_10 ; 
 int countof (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_copy_bytes(void)
{
   VC_CONTAINER_BITS_T bit_stream;
   int error_count = 0;
   uint8_t buffer[countof(bits_0_to_10)];
   uint32_t ii;

   LOG_DEBUG(NULL, "Testing vc_container_bits_copy_bytes");
   BITS_INIT(NULL, &bit_stream, bits_0_to_10, countof(bits_0_to_10));
   memset(buffer, 0, sizeof(buffer));

   /* Copy whole buffer in one go */
   BITS_COPY_BYTES(NULL, &bit_stream, countof(buffer), buffer, "Copy whole buffer");

   if (!BITS_VALID(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Failed to copy the whole buffer");
      error_count++;
   }

   if (memcmp(buffer, bits_0_to_10, countof(bits_0_to_10)) != 0)
   {
      LOG_ERROR(NULL, "Single copy doesn't match original");
      error_count++;
   }

   BITS_INIT(NULL, &bit_stream, bits_0_to_10, countof(bits_0_to_10));
   memset(buffer, 0, sizeof(buffer));

   /* Copy whole buffer one byte at a time */
   for (ii = 0; ii < countof(bits_0_to_10); ii++)
   {
      BITS_COPY_BYTES(NULL, &bit_stream, 1, buffer + ii, "Copy buffer piecemeal");
   }

   if (!BITS_VALID(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Failed to copy the buffer piecemeal");
      error_count++;
   }

   if (memcmp(buffer, bits_0_to_10, countof(bits_0_to_10)) != 0)
   {
      LOG_ERROR(NULL, "Multiple copy doesn't match original");
      error_count++;
   }

   BITS_INIT(NULL, &bit_stream, bits_0_to_10, countof(bits_0_to_10));
   memset(buffer, 0, sizeof(buffer));

   /* Copy part of buffer */
   BITS_SKIP_BYTES(NULL, &bit_stream, 1, "Copy part of buffer");
   BITS_REDUCE_BYTES(NULL, &bit_stream, 1, "Copy part of buffer");
   BITS_COPY_BYTES(NULL, &bit_stream, countof(buffer) - 2, buffer, "Copy part of buffer");

   if (!BITS_VALID(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Failed to copy part of buffer");
      error_count++;
   }

   if (memcmp(buffer, bits_0_to_10 + 1, countof(bits_0_to_10) - 2) != 0)
   {
      LOG_ERROR(NULL, "Partial copy doesn't match original");
      error_count++;
   }

   return error_count;
}