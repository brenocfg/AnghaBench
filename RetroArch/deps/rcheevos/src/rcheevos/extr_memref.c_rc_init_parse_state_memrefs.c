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
struct TYPE_3__ {int /*<<< orphan*/ ** first_memref; } ;
typedef  TYPE_1__ rc_parse_state_t ;
typedef  int /*<<< orphan*/  rc_memref_value_t ;

/* Variables and functions */

void rc_init_parse_state_memrefs(rc_parse_state_t* parse, rc_memref_value_t** memrefs)
{
  parse->first_memref = memrefs;
  *memrefs = 0;
}