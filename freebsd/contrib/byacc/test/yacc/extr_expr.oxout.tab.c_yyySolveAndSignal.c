#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* stackref; TYPE_3__* noderef; } ;
typedef  TYPE_2__ yyyParent ;
struct TYPE_9__ {int prodNum; size_t whichSym; int /*<<< orphan*/  parentIsStack; TYPE_2__ parent; } ;
typedef  TYPE_3__ yyyGNT ;
struct TYPE_11__ {int whichSym; int wa; TYPE_3__* node; } ;
struct TYPE_10__ {long next; int attrbNum; } ;
struct TYPE_7__ {long solvedSAlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  yyyHandleOverflow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yyyIEL ; 
 int* yyyIIEL ; 
 size_t* yyyIIIEL ; 
 size_t yyyLambdaSSAL ; 
 size_t yyyNewSSALC ; 
 TYPE_6__* yyyRSTop ; 
 size_t yyySSALCfreeList ; 
 int /*<<< orphan*/  yyySSALof ; 
 TYPE_5__* yyySSALspace ; 
 long yyySSALspaceSize ; 
 int /*<<< orphan*/  yyySignalEnts (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void yyySolveAndSignal() {
long yyyiDum,*yyypL;
int yyyws,yyywa;
yyyGNT *yyyRSTopN,*yyyRefN; 
yyyParent yyyRSTopNp; 


yyyRSTopNp = (yyyRSTopN = yyyRSTop->node)->parent;
yyyRefN= (yyyws = (yyyRSTop->whichSym))?yyyRSTopNp.noderef:yyyRSTopN;
yyywa = yyyRSTop->wa; 
yyyRSTop--;
switch(yyyRefN->prodNum) {
case 1:  /***yacc rule 1***/
  switch (yyyws) {
  }
break;
case 2:  /***yacc rule 2***/
  switch (yyyws) {
  }
break;
case 3:  /***yacc rule 3***/
  switch (yyyws) {
  }
break;
case 4:  /***yacc rule 4***/
  switch (yyyws) {
  }
break;
case 5:  /***yacc rule 5***/
  switch (yyyws) {
  }
break;
case 6:  /***yacc rule 6***/
  switch (yyyws) {
  }
break;
case 7:  /***yacc rule 7***/
  switch (yyyws) {
  case 1:  /**/
    switch (yyywa) {
    }
  break;
  }
break;
case 8:  /***yacc rule 8***/
  switch (yyyws) {
  case 1:  /**/
    switch (yyywa) {
    }
  break;
  }
break;
} /* switch */ 

if (yyyws)  /* the just-solved instance was inherited. */ 
   {if (yyyRSTopN->prodNum) 
       {yyyiDum = yyyIIEL[yyyIIIEL[yyyRSTopN->prodNum]] + yyywa;
        yyySignalEnts(yyyRSTopN,yyyIEL[yyyiDum],
                                yyyIEL[yyyiDum+1]
                     );
       }
   } 
   else     /* the just-solved instance was synthesized. */ 
   {if (!(yyyRSTopN->parentIsStack)) /* node has a parent. */ 
       {yyyiDum = yyyIIEL[yyyIIIEL[yyyRSTopNp.noderef->prodNum] + 
                          yyyRSTopN->whichSym 
                         ] + 
                  yyywa;
        yyySignalEnts(yyyRSTopNp.noderef,
                      yyyIEL[yyyiDum],
                      yyyIEL[yyyiDum+1] 
                     );
       } 
       else   /* node is still on the stack--it has no parent yet. */ 
       {yyypL = &(yyyRSTopNp.stackref->solvedSAlist); 
        if (yyySSALCfreeList == yyyLambdaSSAL) 
           {yyySSALspace[yyyNewSSALC].next = *yyypL; 
            if ((*yyypL = yyyNewSSALC++) == yyySSALspaceSize) 
               yyyHandleOverflow(yyySSALof); 
           }  
           else
           {yyyiDum = yyySSALCfreeList; 
            yyySSALCfreeList = yyySSALspace[yyySSALCfreeList].next; 
            yyySSALspace[yyyiDum].next = *yyypL; 
            *yyypL = yyyiDum;  
           } 
        yyySSALspace[*yyypL].attrbNum = yyywa; 
       } 
   }

}