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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ipcp_profile_bb_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcp_profile_cs_count_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcp_profile_edge_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcp_profile_mt_count_print (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipcp_profile_print (FILE * f)
{
  fprintf (f, "\nNODE COUNTS :\n");
  ipcp_profile_mt_count_print (f);
  fprintf (f, "\nCS COUNTS stage:\n");
  ipcp_profile_cs_count_print (f);
  fprintf (f, "\nBB COUNTS and FREQUENCIES :\n");
  ipcp_profile_bb_print (f);
  fprintf (f, "\nCFG EDGES COUNTS and PROBABILITIES :\n");
  ipcp_profile_edge_print (f);
}