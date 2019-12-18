#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* noderef; } ;
struct TYPE_7__ {int prodNum; int whichSym; scalar_t__* refCountList; TYPE_2__ parent; int /*<<< orphan*/  parentIsStack; } ;
typedef  TYPE_3__ yyyGNT ;
struct TYPE_5__ {int prodNum; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* yyyAttrbStr (int,int,int) ; 
 char* yyyGSoccurStr (int,int) ; 
 int /*<<< orphan*/  yyyShowProd (int) ; 
 int yyySizeofSort (int) ; 
 int yyySortOf (int,int) ; 

void yyyCheckNodeInstancesSolved(yyyGNT *np)
  {int mysort,sortSize,i,prodNum,symPos,inTerminalNode;
   int nUnsolvedInsts = 0;

   if (np->prodNum != 0)
     {inTerminalNode = 0;
      prodNum = np->prodNum;
      symPos = 0;
     }
   else
     {inTerminalNode = 1;
      prodNum = np->parent.noderef->prodNum;
      symPos = np->whichSym;
     }
   mysort = yyySortOf(prodNum,symPos);
   sortSize = yyySizeofSort(mysort);
   for (i=0; i<sortSize; i++)
     if ((np->refCountList)[i] != 0) nUnsolvedInsts += 1;
   if (nUnsolvedInsts)
     {fprintf(stderr,
      "\nFound node that has %d unsolved attribute instance(s).\n",
              nUnsolvedInsts
             );
      fprintf(stderr,"Node is labeled \"%s\".\n",
             yyyGSoccurStr(prodNum,symPos));
      if (inTerminalNode)
        {fputs("Node is terminal.  Its parent production is:\n  ",stderr);
         yyyShowProd(prodNum);
        }
      else
        {fputs("Node is nonterminal.  ",stderr);
         if (!(np->parentIsStack))
           {fprintf(stderr,
                    "Node is %dth child in its parent production:\n  ",
                   np->whichSym
                  );
            yyyShowProd(np->parent.noderef->prodNum);
           }
         fputs("Node is on left hand side of this production:\n  ",stderr);
         yyyShowProd(np->prodNum);
        }
      fputs("The following instances are unsolved:\n",stderr);
      for (i=0; i<sortSize; i++)
        if ((np->refCountList)[i] != 0)
          fprintf(stderr,"     %-16s still has %1d dependencies.\n",
                  yyyAttrbStr(prodNum,symPos,i),(np->refCountList)[i]);
     }
  }