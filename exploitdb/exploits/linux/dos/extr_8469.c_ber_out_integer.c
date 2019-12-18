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
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  BER_TAG_INTEGER ; 
 int /*<<< orphan*/  ber_out_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint16_be (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ber_out_integer(STREAM s, int value)
{
	ber_out_header(s, BER_TAG_INTEGER, 2);
	out_uint16_be(s, value);
}