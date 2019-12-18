#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct call_site_record {int /*<<< orphan*/  action; int /*<<< orphan*/  landing_pad; } ;
struct TYPE_4__ {TYPE_1__* eh; } ;
struct TYPE_3__ {int call_site_data_used; struct call_site_record* call_site_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 int call_site_base ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  dw2_asm_output_data_uleb128 (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
sjlj_output_call_site_table (void)
{
  int n = cfun->eh->call_site_data_used;
  int i;

  for (i = 0; i < n; ++i)
    {
      struct call_site_record *cs = &cfun->eh->call_site_data[i];

      dw2_asm_output_data_uleb128 (INTVAL (cs->landing_pad),
				   "region %d landing pad", i);
      dw2_asm_output_data_uleb128 (cs->action, "action");
    }

  call_site_base += n;
}