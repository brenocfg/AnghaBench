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
struct chrec_stats {scalar_t__ nb_undetermined; scalar_t__ nb_chrec_dont_know; scalar_t__ nb_higher_poly; scalar_t__ nb_affine_multivar; scalar_t__ nb_affine; scalar_t__ nb_chrecs; } ;

/* Variables and functions */

__attribute__((used)) static inline void
reset_chrecs_counters (struct chrec_stats *stats)
{
  stats->nb_chrecs = 0;
  stats->nb_affine = 0;
  stats->nb_affine_multivar = 0;
  stats->nb_higher_poly = 0;
  stats->nb_chrec_dont_know = 0;
  stats->nb_undetermined = 0;
}