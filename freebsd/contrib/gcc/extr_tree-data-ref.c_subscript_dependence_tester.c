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
struct data_dependence_relation {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_dependence_dependent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDR_A (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  DDR_B (struct data_dependence_relation*) ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  build_classic_dir_vector (struct data_dependence_relation*) ; 
 scalar_t__ build_classic_dist_vector (struct data_dependence_relation*) ; 
 int /*<<< orphan*/  compute_subscript_distance (struct data_dependence_relation*) ; 
 TYPE_1__ dependence_stats ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 scalar_t__ subscript_dependence_tester_1 (struct data_dependence_relation*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
subscript_dependence_tester (struct data_dependence_relation *ddr)
{
  
  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "(subscript_dependence_tester \n");
  
  if (subscript_dependence_tester_1 (ddr, DDR_A (ddr), DDR_B (ddr)))
    dependence_stats.num_dependence_dependent++;

  compute_subscript_distance (ddr);
  if (build_classic_dist_vector (ddr))
    build_classic_dir_vector (ddr);

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, ")\n");
}