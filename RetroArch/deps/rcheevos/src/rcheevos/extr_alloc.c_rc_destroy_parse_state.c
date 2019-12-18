#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ memref; scalar_t__ memref_buffer; } ;
struct TYPE_5__ {TYPE_1__ scratch; } ;
typedef  TYPE_2__ rc_parse_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 

void rc_destroy_parse_state(rc_parse_state_t* parse)
{
  if (parse->scratch.memref != parse->scratch.memref_buffer)
    free(parse->scratch.memref);
}