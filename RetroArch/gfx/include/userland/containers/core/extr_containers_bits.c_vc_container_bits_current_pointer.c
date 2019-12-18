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
struct TYPE_3__ {int /*<<< orphan*/  bits; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int /*<<< orphan*/  vc_container_assert (int) ; 

const uint8_t *vc_container_bits_current_pointer(const VC_CONTAINER_BITS_T *bit_stream)
{
   const uint8_t *buffer = bit_stream->buffer;

   /* Only valid on byte boundaries, where buffer pointer has not been moved yet */
   vc_container_assert(!bit_stream->bits);

   return buffer ? (buffer + 1) : NULL;
}