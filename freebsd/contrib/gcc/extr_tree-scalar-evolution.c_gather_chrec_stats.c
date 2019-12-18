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
typedef  scalar_t__ tree ;
struct chrec_stats {int /*<<< orphan*/  nb_undetermined; int /*<<< orphan*/  nb_higher_poly; int /*<<< orphan*/  nb_affine_multivar; int /*<<< orphan*/  nb_affine; int /*<<< orphan*/  nb_chrecs; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
#define  POLYNOMIAL_CHREC 128 
 int TDF_STATS ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ chrec_contains_undetermined (scalar_t__) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  evolution_function_is_affine_multivariate_p (scalar_t__) ; 
 int /*<<< orphan*/  evolution_function_is_affine_p (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gather_chrec_stats (tree chrec, struct chrec_stats *stats)
{
  if (dump_file && (dump_flags & TDF_STATS))
    {
      fprintf (dump_file, "(classify_chrec ");
      print_generic_expr (dump_file, chrec, 0);
      fprintf (dump_file, "\n");
    }
  
  stats->nb_chrecs++;
  
  if (chrec == NULL_TREE)
    {
      stats->nb_undetermined++;
      return;
    }
  
  switch (TREE_CODE (chrec))
    {
    case POLYNOMIAL_CHREC:
      if (evolution_function_is_affine_p (chrec))
	{
	  if (dump_file && (dump_flags & TDF_STATS))
	    fprintf (dump_file, "  affine_univariate\n");
	  stats->nb_affine++;
	}
      else if (evolution_function_is_affine_multivariate_p (chrec))
	{
	  if (dump_file && (dump_flags & TDF_STATS))
	    fprintf (dump_file, "  affine_multivariate\n");
	  stats->nb_affine_multivar++;
	}
      else
	{
	  if (dump_file && (dump_flags & TDF_STATS))
	    fprintf (dump_file, "  higher_degree_polynomial\n");
	  stats->nb_higher_poly++;
	}
      
      break;

    default:
      break;
    }
  
  if (chrec_contains_undetermined (chrec))
    {
      if (dump_file && (dump_flags & TDF_STATS))
	fprintf (dump_file, "  undetermined\n");
      stats->nb_undetermined++;
    }
  
  if (dump_file && (dump_flags & TDF_STATS))
    fprintf (dump_file, ")\n");
}