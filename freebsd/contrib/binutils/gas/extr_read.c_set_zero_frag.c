#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_2__ {scalar_t__ fr_type; } ;

/* Variables and functions */
 scalar_t__ rs_dummy ; 
 TYPE_1__* symbol_get_frag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_set_frag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_address_frag ; 

__attribute__((used)) static void
set_zero_frag (symbolS *symbolP)
{
  if (symbol_get_frag (symbolP)->fr_type != rs_dummy)
    symbol_set_frag (symbolP, &zero_address_frag);
}