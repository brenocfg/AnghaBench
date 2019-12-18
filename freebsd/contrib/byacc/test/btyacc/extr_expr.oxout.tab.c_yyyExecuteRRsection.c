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
typedef  int /*<<< orphan*/  yyyGNT ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  yyyCheckUnsolvedInstTrav (int /*<<< orphan*/ *,long*,long*) ; 
 int /*<<< orphan*/  yyyDoTraversals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yyyUnsolvedInstSearchTravAux (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yyyYok ; 

void yyyExecuteRRsection(yyyGNT *rootNode)  {
   int yyyi; 
   long cycleSum = 0; 
   long nNZrc = 0; 

   if (!yyyYok) return; 
   yyyCheckUnsolvedInstTrav(rootNode,&nNZrc,&cycleSum);
   if (nNZrc) 
      {
       fputs("\n\n\n**********\n",stderr);
       fputs("cycle detected in completed parse tree",stderr);
       fputs(" after decoration.\n",stderr);
#if CYCLE_VERBOSE
       fprintf(stderr,
               "number of unsolved attribute instances == %ld.\n", 
               nNZrc 
              ); 
       fprintf(stderr,
               "total number of remaining dependencies == %ld.\n", 
               cycleSum
              ); 
       fputs("average number of remaining dependencies\n",stderr);
       fprintf(stderr,"  per unsolved instance == %f.\n", 
               ((float)(cycleSum)/(float)(nNZrc)) 
              ); 
#endif
       fprintf(stderr,
         "searching parse tree for %ld unsolved instances:\n",
               nNZrc
              );
       yyyUnsolvedInstSearchTravAux(rootNode);
      }
   yyyDoTraversals(rootNode);
}