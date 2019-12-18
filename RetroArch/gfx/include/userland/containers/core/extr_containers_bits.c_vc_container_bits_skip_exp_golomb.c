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
 int /*<<< orphan*/  vc_container_bits_get_leading_zero_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_container_bits_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void vc_container_bits_skip_exp_golomb(VC_CONTAINER_BITS_T *bit_stream)
{
   vc_container_bits_skip(bit_stream, vc_container_bits_get_leading_zero_bits(bit_stream));
}