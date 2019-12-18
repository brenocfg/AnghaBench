#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ bytes; } ;
typedef  TYPE_1__ VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int /*<<< orphan*/  vc_container_bits_invalidate (TYPE_1__*) ; 

void vc_container_bits_reduce_bytes(VC_CONTAINER_BITS_T *bit_stream,
      uint32_t bytes_to_reduce)
{
   if (bit_stream->bytes >= bytes_to_reduce)
      bit_stream->bytes -= bytes_to_reduce;
   else
      vc_container_bits_invalidate(bit_stream);
}