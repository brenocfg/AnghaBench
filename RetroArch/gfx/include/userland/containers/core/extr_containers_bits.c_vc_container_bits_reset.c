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
struct TYPE_3__ {scalar_t__ bits; scalar_t__ bytes; } ;
typedef  TYPE_1__ VC_CONTAINER_BITS_T ;

/* Variables and functions */

void vc_container_bits_reset(VC_CONTAINER_BITS_T *bit_stream)
{
   bit_stream->bytes = 0;
   bit_stream->bits = 0;
}