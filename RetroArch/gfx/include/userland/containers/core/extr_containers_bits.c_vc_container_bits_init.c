#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ bits; int /*<<< orphan*/  bytes; int /*<<< orphan*/  const* buffer; } ;
typedef  TYPE_1__ VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int /*<<< orphan*/  vc_container_assert (int /*<<< orphan*/ ) ; 

void vc_container_bits_init(VC_CONTAINER_BITS_T *bit_stream,
      const uint8_t *buffer,
      uint32_t available)
{
   vc_container_assert(buffer && (buffer != (const uint8_t *)1));

   /* Start with buffer pointing at the previous byte with no bits available
    * to make the mathematics easier */
   bit_stream->buffer = buffer - 1;
   bit_stream->bytes = available;
   bit_stream->bits = 0;
}