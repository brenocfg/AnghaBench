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
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ VC_CONTAINER_BITS_T ;

/* Variables and functions */
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int /*<<< orphan*/  vc_container_bits_skip (TYPE_1__*,int) ; 

void vc_container_bits_skip_bytes(VC_CONTAINER_BITS_T *bit_stream,
      uint32_t bytes_to_skip)
{
   /* Only valid on byte boundaries */
   vc_container_assert(!bit_stream->bits);

   vc_container_bits_skip(bit_stream, bytes_to_skip << 3);
}