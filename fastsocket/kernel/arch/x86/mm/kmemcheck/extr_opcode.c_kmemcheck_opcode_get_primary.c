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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ opcode_is_prefix (int /*<<< orphan*/  const) ; 
 scalar_t__ opcode_is_rex_prefix (int /*<<< orphan*/  const) ; 

const uint8_t *kmemcheck_opcode_get_primary(const uint8_t *op)
{
	/* skip prefixes */
	while (opcode_is_prefix(*op))
		++op;
	if (opcode_is_rex_prefix(*op))
		++op;
	return op;
}