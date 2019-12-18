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
 TYPE_2__* cfun ; 
 scalar_t__ size_of_uleb128 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sjlj_size_of_call_site_table (void)
{
  int n = cfun->eh->call_site_data_used;
  int size = 0;
  int i;

  for (i = 0; i < n; ++i)
    {
      struct call_site_record *cs = &cfun->eh->call_site_data[i];
      size += size_of_uleb128 (INTVAL (cs->landing_pad));
      size += size_of_uleb128 (cs->action);
    }

  return size;
}