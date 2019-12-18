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
struct scev_info_str {int /*<<< orphan*/  chrec; } ;
struct chrec_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gather_chrec_stats (int /*<<< orphan*/ ,struct chrec_stats*) ; 

__attribute__((used)) static int
gather_stats_on_scev_database_1 (void **slot, void *stats)
{
  struct scev_info_str *entry = (struct scev_info_str *) *slot;

  gather_chrec_stats (entry->chrec, (struct chrec_stats *) stats);

  return 1;
}