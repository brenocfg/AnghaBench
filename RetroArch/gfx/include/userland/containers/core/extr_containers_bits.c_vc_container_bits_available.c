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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int bytes; scalar_t__ bits; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ VC_CONTAINER_BITS_T ;

/* Variables and functions */

uint32_t vc_container_bits_available(const VC_CONTAINER_BITS_T *bit_stream)
{
   if (!bit_stream->buffer)
      return 0;
   return (bit_stream->bytes << 3) + bit_stream->bits;
}