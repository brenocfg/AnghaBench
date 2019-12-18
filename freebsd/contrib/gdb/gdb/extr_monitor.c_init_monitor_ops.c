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
struct target_ops {int dummy; } ;
struct TYPE_3__ {scalar_t__ to_magic; } ;

/* Variables and functions */
 scalar_t__ OPS_MAGIC ; 
 int /*<<< orphan*/  init_base_monitor_ops () ; 
 int /*<<< orphan*/  memcpy (struct target_ops*,TYPE_1__*,int) ; 
 TYPE_1__ monitor_ops ; 

void
init_monitor_ops (struct target_ops *ops)
{
  if (monitor_ops.to_magic != OPS_MAGIC)
    init_base_monitor_ops ();

  memcpy (ops, &monitor_ops, sizeof monitor_ops);
}