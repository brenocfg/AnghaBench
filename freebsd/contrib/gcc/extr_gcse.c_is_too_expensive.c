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
typedef  int /*<<< orphan*/  SBITMAP_ELT_TYPE ;

/* Variables and functions */
 int MAX_GCSE_MEMORY ; 
 int /*<<< orphan*/  OPT_Wdisabled_optimization ; 
 int SBITMAP_SET_SIZE (int) ; 
 int max_reg_num () ; 
 int n_basic_blocks ; 
 int n_edges ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,char const*,int,int) ; 

__attribute__((used)) static bool
is_too_expensive (const char *pass)
{
  /* Trying to perform global optimizations on flow graphs which have
     a high connectivity will take a long time and is unlikely to be
     particularly useful.

     In normal circumstances a cfg should have about twice as many
     edges as blocks.  But we do not want to punish small functions
     which have a couple switch statements.  Rather than simply
     threshold the number of blocks, uses something with a more
     graceful degradation.  */
  if (n_edges > 20000 + n_basic_blocks * 4)
    {
      warning (OPT_Wdisabled_optimization,
	       "%s: %d basic blocks and %d edges/basic block",
	       pass, n_basic_blocks, n_edges / n_basic_blocks);

      return true;
    }

  /* If allocating memory for the cprop bitmap would take up too much
     storage it's better just to disable the optimization.  */
  if ((n_basic_blocks
       * SBITMAP_SET_SIZE (max_reg_num ())
       * sizeof (SBITMAP_ELT_TYPE)) > MAX_GCSE_MEMORY)
    {
      warning (OPT_Wdisabled_optimization,
	       "%s: %d basic blocks and %d registers",
	       pass, n_basic_blocks, max_reg_num ());

      return true;
    }

  return false;
}