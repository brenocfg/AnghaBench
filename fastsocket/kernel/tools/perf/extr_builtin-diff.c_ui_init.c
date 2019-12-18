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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  COMPUTE_DELTA 130 
#define  COMPUTE_RATIO 129 
#define  COMPUTE_WEIGHTED_DIFF 128 
 int /*<<< orphan*/  PERF_HPP__BASELINE ; 
 int /*<<< orphan*/  PERF_HPP__DELTA ; 
 int /*<<< orphan*/  PERF_HPP__DISPL ; 
 int /*<<< orphan*/  PERF_HPP__FORMULA ; 
 int /*<<< orphan*/  PERF_HPP__OVERHEAD ; 
 int /*<<< orphan*/  PERF_HPP__PERIOD ; 
 int /*<<< orphan*/  PERF_HPP__PERIOD_BASELINE ; 
 int /*<<< orphan*/  PERF_HPP__RATIO ; 
 int /*<<< orphan*/  PERF_HPP__WEIGHTED_DIFF ; 
 int compute ; 
 int /*<<< orphan*/  perf_hpp__column_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_hpp__init () ; 
 scalar_t__ show_displacement ; 
 scalar_t__ show_formula ; 
 scalar_t__ show_period ; 

__attribute__((used)) static void ui_init(void)
{
	perf_hpp__init();

	/* No overhead column. */
	perf_hpp__column_enable(PERF_HPP__OVERHEAD, false);

	/*
	 * Display baseline/delta/ratio/displacement/
	 * formula/periods columns.
	 */
	perf_hpp__column_enable(PERF_HPP__BASELINE, true);

	switch (compute) {
	case COMPUTE_DELTA:
		perf_hpp__column_enable(PERF_HPP__DELTA, true);
		break;
	case COMPUTE_RATIO:
		perf_hpp__column_enable(PERF_HPP__RATIO, true);
		break;
	case COMPUTE_WEIGHTED_DIFF:
		perf_hpp__column_enable(PERF_HPP__WEIGHTED_DIFF, true);
		break;
	default:
		BUG_ON(1);
	};

	if (show_displacement)
		perf_hpp__column_enable(PERF_HPP__DISPL, true);

	if (show_formula)
		perf_hpp__column_enable(PERF_HPP__FORMULA, true);

	if (show_period) {
		perf_hpp__column_enable(PERF_HPP__PERIOD, true);
		perf_hpp__column_enable(PERF_HPP__PERIOD_BASELINE, true);
	}
}