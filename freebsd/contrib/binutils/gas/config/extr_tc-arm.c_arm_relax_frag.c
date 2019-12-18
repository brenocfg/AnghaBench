#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int fr_var; int fr_subtype; } ;
typedef  TYPE_1__ fragS ;
struct TYPE_16__ {int /*<<< orphan*/  owner; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
#define  T_MNEM_add_pc 152 
#define  T_MNEM_add_sp 151 
#define  T_MNEM_addi 150 
#define  T_MNEM_addis 149 
#define  T_MNEM_adr 148 
#define  T_MNEM_b 147 
#define  T_MNEM_bcond 146 
#define  T_MNEM_cmn 145 
#define  T_MNEM_cmp 144 
#define  T_MNEM_dec_sp 143 
#define  T_MNEM_inc_sp 142 
#define  T_MNEM_ldr 141 
#define  T_MNEM_ldr_pc 140 
#define  T_MNEM_ldr_pc2 139 
#define  T_MNEM_ldr_sp 138 
#define  T_MNEM_ldrb 137 
#define  T_MNEM_ldrh 136 
#define  T_MNEM_mov 135 
#define  T_MNEM_movs 134 
#define  T_MNEM_str 133 
#define  T_MNEM_str_sp 132 
#define  T_MNEM_strb 131 
#define  T_MNEM_strh 130 
#define  T_MNEM_subi 129 
#define  T_MNEM_subis 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  frag_wane (TYPE_1__*) ; 
 int /*<<< orphan*/  md_convert_frag (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*) ; 
 int relax_addsub (TYPE_1__*,TYPE_2__*) ; 
 int relax_adr (TYPE_1__*,TYPE_2__*,long) ; 
 int relax_branch (TYPE_1__*,TYPE_2__*,int,long) ; 
 int relax_immediate (TYPE_1__*,int,int) ; 

int
arm_relax_frag (asection *sec, fragS *fragp, long stretch)
{
  int oldsize;
  int newsize;

  oldsize = fragp->fr_var;
  switch (fragp->fr_subtype)
    {
    case T_MNEM_ldr_pc2:
      newsize = relax_adr(fragp, sec, stretch);
      break;
    case T_MNEM_ldr_pc:
    case T_MNEM_ldr_sp:
    case T_MNEM_str_sp:
      newsize = relax_immediate(fragp, 8, 2);
      break;
    case T_MNEM_ldr:
    case T_MNEM_str:
      newsize = relax_immediate(fragp, 5, 2);
      break;
    case T_MNEM_ldrh:
    case T_MNEM_strh:
      newsize = relax_immediate(fragp, 5, 1);
      break;
    case T_MNEM_ldrb:
    case T_MNEM_strb:
      newsize = relax_immediate(fragp, 5, 0);
      break;
    case T_MNEM_adr:
      newsize = relax_adr(fragp, sec, stretch);
      break;
    case T_MNEM_mov:
    case T_MNEM_movs:
    case T_MNEM_cmp:
    case T_MNEM_cmn:
      newsize = relax_immediate(fragp, 8, 0);
      break;
    case T_MNEM_b:
      newsize = relax_branch(fragp, sec, 11, stretch);
      break;
    case T_MNEM_bcond:
      newsize = relax_branch(fragp, sec, 8, stretch);
      break;
    case T_MNEM_add_sp:
    case T_MNEM_add_pc:
      newsize = relax_immediate (fragp, 8, 2);
      break;
    case T_MNEM_inc_sp:
    case T_MNEM_dec_sp:
      newsize = relax_immediate (fragp, 7, 2);
      break;
    case T_MNEM_addi:
    case T_MNEM_addis:
    case T_MNEM_subi:
    case T_MNEM_subis:
      newsize = relax_addsub (fragp, sec);
      break;
    default:
      abort();
    }

  fragp->fr_var = newsize;
  /* Freeze wide instructions that are at or before the same location as
     in the previous pass.  This avoids infinite loops.
     Don't freeze them unconditionally because targets may be artificialy
     misaligned by the expansion of preceeding frags.  */
  if (stretch <= 0 && newsize > 2)
    {
      md_convert_frag (sec->owner, sec, fragp);
      frag_wane(fragp);
    }

  return newsize - oldsize;
}