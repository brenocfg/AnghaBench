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
struct ni_gpct {int dummy; } ;
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;

/* Variables and functions */
 int /*<<< orphan*/  ni_tio_set_bits_transient (struct ni_gpct*,int,unsigned int,unsigned int,int) ; 

__attribute__((used)) static inline void ni_tio_set_bits(struct ni_gpct *counter,
				   enum ni_gpct_register register_index,
				   unsigned bit_mask, unsigned bit_values)
{
	ni_tio_set_bits_transient(counter, register_index, bit_mask, bit_values,
				  0x0);
}