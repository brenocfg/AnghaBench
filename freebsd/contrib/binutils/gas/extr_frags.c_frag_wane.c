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
struct TYPE_3__ {scalar_t__ fr_var; scalar_t__ fr_offset; int /*<<< orphan*/  fr_type; } ;
typedef  TYPE_1__ fragS ;

/* Variables and functions */
 int /*<<< orphan*/  rs_fill ; 

void
frag_wane (register fragS *fragP)
{
  fragP->fr_type = rs_fill;
  fragP->fr_offset = 0;
  fragP->fr_var = 0;
}