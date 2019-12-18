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
struct TYPE_3__ {struct eh_region* prev_try; } ;
struct TYPE_4__ {TYPE_1__ cleanup; } ;
struct eh_region {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERT_CLEANUP ; 
 struct eh_region* gen_eh_region (int /*<<< orphan*/ ,struct eh_region*) ; 

struct eh_region *
gen_eh_region_cleanup (struct eh_region *outer, struct eh_region *prev_try)
{
  struct eh_region *cleanup = gen_eh_region (ERT_CLEANUP, outer);
  cleanup->u.cleanup.prev_try = prev_try;
  return cleanup;
}