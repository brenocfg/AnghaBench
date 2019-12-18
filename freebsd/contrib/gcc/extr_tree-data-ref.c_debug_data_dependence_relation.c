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
struct data_dependence_relation {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_data_dependence_relation (int /*<<< orphan*/ ,struct data_dependence_relation*) ; 
 int /*<<< orphan*/  stderr ; 

void 
debug_data_dependence_relation (struct data_dependence_relation *ddr)
{
  dump_data_dependence_relation (stderr, ddr);
}