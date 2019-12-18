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
struct chrec_stats {int nb_affine; int nb_affine_multivar; int nb_higher_poly; int nb_chrec_dont_know; int nb_chrecs; int nb_undetermined; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ htab_elements (int /*<<< orphan*/ ) ; 
 int nb_get_scev ; 
 int nb_set_scev ; 
 int /*<<< orphan*/  scalar_evolution_info ; 

__attribute__((used)) static void
dump_chrecs_stats (FILE *file, struct chrec_stats *stats)
{
  fprintf (file, "\n(\n");
  fprintf (file, "-----------------------------------------\n");
  fprintf (file, "%d\taffine univariate chrecs\n", stats->nb_affine);
  fprintf (file, "%d\taffine multivariate chrecs\n", stats->nb_affine_multivar);
  fprintf (file, "%d\tdegree greater than 2 polynomials\n", 
	   stats->nb_higher_poly);
  fprintf (file, "%d\tchrec_dont_know chrecs\n", stats->nb_chrec_dont_know);
  fprintf (file, "-----------------------------------------\n");
  fprintf (file, "%d\ttotal chrecs\n", stats->nb_chrecs);
  fprintf (file, "%d\twith undetermined coefficients\n", 
	   stats->nb_undetermined);
  fprintf (file, "-----------------------------------------\n");
  fprintf (file, "%d\tchrecs in the scev database\n", 
	   (int) htab_elements (scalar_evolution_info));
  fprintf (file, "%d\tsets in the scev database\n", nb_set_scev);
  fprintf (file, "%d\tgets in the scev database\n", nb_get_scev);
  fprintf (file, "-----------------------------------------\n");
  fprintf (file, ")\n\n");
}