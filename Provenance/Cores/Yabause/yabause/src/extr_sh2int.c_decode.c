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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/ * opcodefunc ;

/* Variables and functions */
 int INSTRUCTION_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTRUCTION_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTRUCTION_C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTRUCTION_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2add ; 
 int /*<<< orphan*/  SH2addc ; 
 int /*<<< orphan*/  SH2addi ; 
 int /*<<< orphan*/  SH2addv ; 
 int /*<<< orphan*/  SH2andi ; 
 int /*<<< orphan*/  SH2andm ; 
 int /*<<< orphan*/  SH2bf ; 
 int /*<<< orphan*/  SH2bfs ; 
 int /*<<< orphan*/  SH2bra ; 
 int /*<<< orphan*/  SH2braf ; 
 int /*<<< orphan*/  SH2bsr ; 
 int /*<<< orphan*/  SH2bsrf ; 
 int /*<<< orphan*/  SH2bt ; 
 int /*<<< orphan*/  SH2bts ; 
 int /*<<< orphan*/  SH2clrmac ; 
 int /*<<< orphan*/  SH2clrt ; 
 int /*<<< orphan*/  SH2cmpeq ; 
 int /*<<< orphan*/  SH2cmpge ; 
 int /*<<< orphan*/  SH2cmpgt ; 
 int /*<<< orphan*/  SH2cmphi ; 
 int /*<<< orphan*/  SH2cmphs ; 
 int /*<<< orphan*/  SH2cmpim ; 
 int /*<<< orphan*/  SH2cmppl ; 
 int /*<<< orphan*/  SH2cmppz ; 
 int /*<<< orphan*/  SH2cmpstr ; 
 int /*<<< orphan*/  SH2div0s ; 
 int /*<<< orphan*/  SH2div0u ; 
 int /*<<< orphan*/  SH2div1 ; 
 int /*<<< orphan*/  SH2dmuls ; 
 int /*<<< orphan*/  SH2dmulu ; 
 int /*<<< orphan*/  SH2dt ; 
 int /*<<< orphan*/  SH2extsb ; 
 int /*<<< orphan*/  SH2extsw ; 
 int /*<<< orphan*/  SH2extub ; 
 int /*<<< orphan*/  SH2extuw ; 
 int /*<<< orphan*/  SH2jmp ; 
 int /*<<< orphan*/  SH2jsr ; 
 int /*<<< orphan*/  SH2ldcgbr ; 
 int /*<<< orphan*/  SH2ldcmgbr ; 
 int /*<<< orphan*/  SH2ldcmsr ; 
 int /*<<< orphan*/  SH2ldcmvbr ; 
 int /*<<< orphan*/  SH2ldcsr ; 
 int /*<<< orphan*/  SH2ldcvbr ; 
 int /*<<< orphan*/  SH2ldsmach ; 
 int /*<<< orphan*/  SH2ldsmacl ; 
 int /*<<< orphan*/  SH2ldsmmach ; 
 int /*<<< orphan*/  SH2ldsmmacl ; 
 int /*<<< orphan*/  SH2ldsmpr ; 
 int /*<<< orphan*/  SH2ldspr ; 
 int /*<<< orphan*/  SH2macl ; 
 int /*<<< orphan*/  SH2macw ; 
 int /*<<< orphan*/  SH2mov ; 
 int /*<<< orphan*/  SH2mova ; 
 int /*<<< orphan*/  SH2movbl ; 
 int /*<<< orphan*/  SH2movbl0 ; 
 int /*<<< orphan*/  SH2movbl4 ; 
 int /*<<< orphan*/  SH2movblg ; 
 int /*<<< orphan*/  SH2movbm ; 
 int /*<<< orphan*/  SH2movbp ; 
 int /*<<< orphan*/  SH2movbs ; 
 int /*<<< orphan*/  SH2movbs0 ; 
 int /*<<< orphan*/  SH2movbs4 ; 
 int /*<<< orphan*/  SH2movbsg ; 
 int /*<<< orphan*/  SH2movi ; 
 int /*<<< orphan*/  SH2movli ; 
 int /*<<< orphan*/  SH2movll ; 
 int /*<<< orphan*/  SH2movll0 ; 
 int /*<<< orphan*/  SH2movll4 ; 
 int /*<<< orphan*/  SH2movllg ; 
 int /*<<< orphan*/  SH2movlm ; 
 int /*<<< orphan*/  SH2movlp ; 
 int /*<<< orphan*/  SH2movls ; 
 int /*<<< orphan*/  SH2movls0 ; 
 int /*<<< orphan*/  SH2movls4 ; 
 int /*<<< orphan*/  SH2movlsg ; 
 int /*<<< orphan*/  SH2movt ; 
 int /*<<< orphan*/  SH2movwi ; 
 int /*<<< orphan*/  SH2movwl ; 
 int /*<<< orphan*/  SH2movwl0 ; 
 int /*<<< orphan*/  SH2movwl4 ; 
 int /*<<< orphan*/  SH2movwlg ; 
 int /*<<< orphan*/  SH2movwm ; 
 int /*<<< orphan*/  SH2movwp ; 
 int /*<<< orphan*/  SH2movws ; 
 int /*<<< orphan*/  SH2movws0 ; 
 int /*<<< orphan*/  SH2movws4 ; 
 int /*<<< orphan*/  SH2movwsg ; 
 int /*<<< orphan*/  SH2mull ; 
 int /*<<< orphan*/  SH2muls ; 
 int /*<<< orphan*/  SH2mulu ; 
 int /*<<< orphan*/  SH2neg ; 
 int /*<<< orphan*/  SH2negc ; 
 int /*<<< orphan*/  SH2nop ; 
 int /*<<< orphan*/  SH2ori ; 
 int /*<<< orphan*/  SH2orm ; 
 int /*<<< orphan*/  SH2rotcl ; 
 int /*<<< orphan*/  SH2rotcr ; 
 int /*<<< orphan*/  SH2rotl ; 
 int /*<<< orphan*/  SH2rotr ; 
 int /*<<< orphan*/  SH2rte ; 
 int /*<<< orphan*/  SH2rts ; 
 int /*<<< orphan*/  SH2sett ; 
 int /*<<< orphan*/  SH2shal ; 
 int /*<<< orphan*/  SH2shar ; 
 int /*<<< orphan*/  SH2shll ; 
 int /*<<< orphan*/  SH2shll16 ; 
 int /*<<< orphan*/  SH2shll2 ; 
 int /*<<< orphan*/  SH2shll8 ; 
 int /*<<< orphan*/  SH2shlr ; 
 int /*<<< orphan*/  SH2shlr16 ; 
 int /*<<< orphan*/  SH2shlr2 ; 
 int /*<<< orphan*/  SH2shlr8 ; 
 int /*<<< orphan*/  SH2sleep ; 
 int /*<<< orphan*/  SH2stcgbr ; 
 int /*<<< orphan*/  SH2stcmgbr ; 
 int /*<<< orphan*/  SH2stcmsr ; 
 int /*<<< orphan*/  SH2stcmvbr ; 
 int /*<<< orphan*/  SH2stcsr ; 
 int /*<<< orphan*/  SH2stcvbr ; 
 int /*<<< orphan*/  SH2stsmach ; 
 int /*<<< orphan*/  SH2stsmacl ; 
 int /*<<< orphan*/  SH2stsmmach ; 
 int /*<<< orphan*/  SH2stsmmacl ; 
 int /*<<< orphan*/  SH2stsmpr ; 
 int /*<<< orphan*/  SH2stspr ; 
 int /*<<< orphan*/  SH2sub ; 
 int /*<<< orphan*/  SH2subc ; 
 int /*<<< orphan*/  SH2subv ; 
 int /*<<< orphan*/  SH2swapb ; 
 int /*<<< orphan*/  SH2swapw ; 
 int /*<<< orphan*/  SH2tas ; 
 int /*<<< orphan*/  SH2trapa ; 
 int /*<<< orphan*/  SH2tst ; 
 int /*<<< orphan*/  SH2tsti ; 
 int /*<<< orphan*/  SH2tstm ; 
 int /*<<< orphan*/  SH2undecoded ; 
 int /*<<< orphan*/  SH2xori ; 
 int /*<<< orphan*/  SH2xorm ; 
 int /*<<< orphan*/  SH2xtrct ; 
 int /*<<< orphan*/  SH2y_and ; 
 int /*<<< orphan*/  SH2y_not ; 
 int /*<<< orphan*/  SH2y_or ; 
 int /*<<< orphan*/  SH2y_xor ; 

__attribute__((used)) static opcodefunc decode(u16 instruction)
{
   switch (INSTRUCTION_A(instruction))
   {
      case 0:
         switch (INSTRUCTION_D(instruction))
         {
            case 2:
               switch (INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2stcsr;
                  case 1: return &SH2stcgbr;
                  case 2: return &SH2stcvbr;
                  default: return &SH2undecoded;
               }
     
            case 3:
               switch (INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2bsrf;
                  case 2: return &SH2braf;
                  default: return &SH2undecoded;
               }
     
            case 4: return &SH2movbs0;
            case 5: return &SH2movws0;
            case 6: return &SH2movls0;
            case 7: return &SH2mull;
            case 8:
               switch (INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2clrt;
                  case 1: return &SH2sett;
                  case 2: return &SH2clrmac;
                  default: return &SH2undecoded;
               }     
            case 9:
               switch (INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2nop;
                  case 1: return &SH2div0u;
                  case 2: return &SH2movt;
                  default: return &SH2undecoded;
               }     
            case 10:
               switch (INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2stsmach;
                  case 1: return &SH2stsmacl;
                  case 2: return &SH2stspr;
                  default: return &SH2undecoded;
               }     
            case 11:
               switch (INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2rts;
                  case 1: return &SH2sleep;
                  case 2: return &SH2rte;
                  default: return &SH2undecoded;
               }     
            case 12: return &SH2movbl0;
            case 13: return &SH2movwl0;
            case 14: return &SH2movll0;
            case 15: return &SH2macl;
            default: return &SH2undecoded;
         }
   
      case 1: return &SH2movls4;
      case 2:
         switch (INSTRUCTION_D(instruction))
         {
            case 0: return &SH2movbs;
            case 1: return &SH2movws;
            case 2: return &SH2movls;
            case 4: return &SH2movbm;
            case 5: return &SH2movwm;
            case 6: return &SH2movlm;
            case 7: return &SH2div0s;
            case 8: return &SH2tst;
            case 9: return &SH2y_and;
            case 10: return &SH2y_xor;
            case 11: return &SH2y_or;
            case 12: return &SH2cmpstr;
            case 13: return &SH2xtrct;
            case 14: return &SH2mulu;
            case 15: return &SH2muls;
            default: return &SH2undecoded;
         }
   
      case 3:
         switch(INSTRUCTION_D(instruction))
         {
            case 0:  return &SH2cmpeq;
            case 2:  return &SH2cmphs;
            case 3:  return &SH2cmpge;
            case 4:  return &SH2div1;
            case 5:  return &SH2dmulu;
            case 6:  return &SH2cmphi;
            case 7:  return &SH2cmpgt;
            case 8:  return &SH2sub;
            case 10: return &SH2subc;
            case 11: return &SH2subv;
            case 12: return &SH2add;
            case 13: return &SH2dmuls;
            case 14: return &SH2addc;
            case 15: return &SH2addv;
            default: return &SH2undecoded;
         }
   
      case 4:
         switch(INSTRUCTION_D(instruction))
         {
            case 0:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2shll;
                  case 1: return &SH2dt;
                  case 2: return &SH2shal;
                  default: return &SH2undecoded;
               }
            case 1:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2shlr;
                  case 1: return &SH2cmppz;
                  case 2: return &SH2shar;
                  default: return &SH2undecoded;
               }     
            case 2:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2stsmmach;
                  case 1: return &SH2stsmmacl;
                  case 2: return &SH2stsmpr;
                  default: return &SH2undecoded;
               }
            case 3:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2stcmsr;
                  case 1: return &SH2stcmgbr;
                  case 2: return &SH2stcmvbr;
                  default: return &SH2undecoded;
               }
            case 4:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2rotl;
                  case 2: return &SH2rotcl;
                  default: return &SH2undecoded;
               }     
            case 5:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2rotr;
                  case 1: return &SH2cmppl;
                  case 2: return &SH2rotcr;
                  default: return &SH2undecoded;
               }                 
            case 6:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2ldsmmach;
                  case 1: return &SH2ldsmmacl;
                  case 2: return &SH2ldsmpr;
                  default: return &SH2undecoded;
               }     
            case 7:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2ldcmsr;
                  case 1: return &SH2ldcmgbr;
                  case 2: return &SH2ldcmvbr;
                  default: return &SH2undecoded;
               }     
            case 8:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2shll2;
                  case 1: return &SH2shll8;
                  case 2: return &SH2shll16;
                  default: return &SH2undecoded;
               }     
            case 9:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2shlr2;
                  case 1: return &SH2shlr8;
                  case 2: return &SH2shlr16;
                  default: return &SH2undecoded;
               }     
            case 10:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2ldsmach;
                  case 1: return &SH2ldsmacl;
                  case 2: return &SH2ldspr;
                  default: return &SH2undecoded;
               }     
            case 11:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2jsr;
                  case 1: return &SH2tas;
                  case 2: return &SH2jmp;
                  default: return &SH2undecoded;
               }     
            case 14:
               switch(INSTRUCTION_C(instruction))
               {
                  case 0: return &SH2ldcsr;
                  case 1: return &SH2ldcgbr;
                  case 2: return &SH2ldcvbr;
                  default: return &SH2undecoded;
               }
            case 15: return &SH2macw;
            default: return &SH2undecoded;
         }
      case 5: return &SH2movll4;
      case 6:
         switch (INSTRUCTION_D(instruction))
         {
            case 0:  return &SH2movbl;
            case 1:  return &SH2movwl;
            case 2:  return &SH2movll;
            case 3:  return &SH2mov;
            case 4:  return &SH2movbp;
            case 5:  return &SH2movwp;
            case 6:  return &SH2movlp;
            case 7:  return &SH2y_not;
            case 8:  return &SH2swapb;
            case 9:  return &SH2swapw;
            case 10: return &SH2negc;
            case 11: return &SH2neg;
            case 12: return &SH2extub;
            case 13: return &SH2extuw;
            case 14: return &SH2extsb;
            case 15: return &SH2extsw;
         }
   
      case 7: return &SH2addi;
      case 8:
         switch (INSTRUCTION_B(instruction))
         {
            case 0:  return &SH2movbs4;
            case 1:  return &SH2movws4;
            case 4:  return &SH2movbl4;
            case 5:  return &SH2movwl4;
            case 8:  return &SH2cmpim;
            case 9:  return &SH2bt;
            case 11: return &SH2bf;
            case 13: return &SH2bts;
            case 15: return &SH2bfs;
            default: return &SH2undecoded;
         }   
      case 9: return &SH2movwi;
      case 10: return &SH2bra;
      case 11: return &SH2bsr;
      case 12:
         switch(INSTRUCTION_B(instruction))
         {
            case 0:  return &SH2movbsg;
            case 1:  return &SH2movwsg;
            case 2:  return &SH2movlsg;
            case 3:  return &SH2trapa;
            case 4:  return &SH2movblg;
            case 5:  return &SH2movwlg;
            case 6:  return &SH2movllg;
            case 7:  return &SH2mova;
            case 8:  return &SH2tsti;
            case 9:  return &SH2andi;
            case 10: return &SH2xori;
            case 11: return &SH2ori;
            case 12: return &SH2tstm;
            case 13: return &SH2andm;
            case 14: return &SH2xorm;
            case 15: return &SH2orm;
         }
   
      case 13: return &SH2movli;
      case 14: return &SH2movi;
      default: return &SH2undecoded;
   }
}