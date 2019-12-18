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
typedef  int /*<<< orphan*/  uint32_t ;
struct bitstream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitstream_peek (struct bitstream*,int) ; 
 int /*<<< orphan*/  bitstream_remove (struct bitstream*,int) ; 

uint32_t bitstream_read(struct bitstream* bitstream, int numbits)
{
	uint32_t result = bitstream_peek(bitstream, numbits);
	bitstream_remove(bitstream, numbits);
	return result;
}