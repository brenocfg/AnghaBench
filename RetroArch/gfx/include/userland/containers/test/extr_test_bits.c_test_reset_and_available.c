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
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;

/* Variables and functions */
 scalar_t__ BITS_AVAILABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITS_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BITS_RESET (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bits_0_to_10 ; 
 int /*<<< orphan*/  countof (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_reset_and_available(void)
{
   VC_CONTAINER_BITS_T bit_stream;
   int error_count = 0;

   LOG_DEBUG(NULL, "Testing vc_container_bits_reset and vc_container_bits_available");
   BITS_INIT(NULL, &bit_stream, bits_0_to_10, countof(bits_0_to_10));

   if (!BITS_AVAILABLE(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Expected initialised stream to contain bits");
      error_count++;
   }

   BITS_RESET(NULL, &bit_stream);

   if (BITS_AVAILABLE(NULL, &bit_stream))
   {
      LOG_ERROR(NULL, "Expected reset stream not to contain bits");
      error_count++;
   }

   return error_count;
}