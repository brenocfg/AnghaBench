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
struct regstat {int dummy; } ;

/* Variables and functions */
#define  ALU 144 
#define  CJUMP 143 
#define  COMPLEX 142 
#define  EXT 141 
#define  FLAGS 140 
#define  IMM8 139 
#define  LOAD 138 
#define  MOV 137 
#define  MULTDIV 136 
#define  PCREL 135 
#define  RJUMP 134 
#define  RMW 133 
#define  SHIFTIMM 132 
#define  SJUMP 131 
#define  STORE 130 
#define  SYSCALL 129 
#define  UJUMP 128 
 int /*<<< orphan*/  alu_alloc (struct regstat*,int) ; 
 int /*<<< orphan*/  assem_debug (char*) ; 
 int /*<<< orphan*/  complex_alloc (struct regstat*,int) ; 
 int /*<<< orphan*/  ext_alloc (struct regstat*,int) ; 
 int /*<<< orphan*/  flags_alloc (struct regstat*,int) ; 
 int /*<<< orphan*/  imm8_alloc (struct regstat*,int) ; 
 int* itype ; 
 int /*<<< orphan*/  load_alloc (struct regstat*,int) ; 
 int /*<<< orphan*/  mov_alloc (struct regstat*,int) ; 
 int /*<<< orphan*/  multdiv_alloc (struct regstat*,int) ; 
 int /*<<< orphan*/  pcrel_alloc (struct regstat*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rmw_alloc (struct regstat*,int) ; 
 int /*<<< orphan*/  shiftimm_alloc (struct regstat*,int) ; 
 int stop_after_jal ; 
 int /*<<< orphan*/  store_alloc (struct regstat*,int) ; 

void delayslot_alloc(struct regstat *current,int i)
{
  switch(itype[i]) {
    case UJUMP:
    case CJUMP:
    case SJUMP:
    case RJUMP:
    case SYSCALL:
      assem_debug("jump in the delay slot.  this shouldn't happen.\n");//exit(1);
      printf("Disabled speculative precompilation\n");
      stop_after_jal=1;
      break;
    case IMM8:
      imm8_alloc(current,i);
      break;
    case LOAD:
      load_alloc(current,i);
      break;
    case STORE:
      store_alloc(current,i);
      break;
    case RMW:
      rmw_alloc(current,i);
      break;
    case PCREL:
      pcrel_alloc(current,i);
      break;
    case ALU:
      alu_alloc(current,i);
      break;
    case MULTDIV:
      multdiv_alloc(current,i);
      break;
    case SHIFTIMM:
      shiftimm_alloc(current,i);
      break;
    case MOV:
      mov_alloc(current,i);
      break;
    case EXT:
      ext_alloc(current,i);
      break;
    case FLAGS:
      flags_alloc(current,i);
      break;
    case COMPLEX:
      complex_alloc(current,i);
      break;
  }
}