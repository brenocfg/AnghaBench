#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct neon_type_el {int size; int /*<<< orphan*/  type; } ;
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_4__ {int instruction; TYPE_1__* operands; int /*<<< orphan*/ * error; } ;
struct TYPE_3__ {unsigned int reg; int imm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* BAD_FPU ; 
 int /*<<< orphan*/  FAIL ; 
 int HI1 (unsigned int) ; 
 int LOW4 (unsigned int) ; 
 int NEON_CHECK_ARCH ; 
 int NEON_CHECK_CC ; 
 unsigned int NEON_SCALAR_INDEX (int) ; 
 unsigned int NEON_SCALAR_REG (int) ; 
#define  NS_DD 141 
#define  NS_DI 140 
#define  NS_DRR 139 
#define  NS_FF 138 
#define  NS_FFRR 137 
#define  NS_FI 136 
#define  NS_FR 135 
 int NS_NULL ; 
#define  NS_QI 134 
#define  NS_QQ 133 
#define  NS_RF 132 
#define  NS_RRD 131 
#define  NS_RRFF 130 
#define  NS_RS 129 
#define  NS_SR 128 
 int /*<<< orphan*/  NT_float ; 
 int /*<<< orphan*/  NT_invtype ; 
 int /*<<< orphan*/  NT_signed ; 
 int N_16 ; 
 int N_32 ; 
 int N_8 ; 
 int N_EQK ; 
 int N_F64 ; 
 int N_KEY ; 
 int N_S16 ; 
 int N_S8 ; 
 int N_U16 ; 
 int N_U8 ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_variant ; 
 int /*<<< orphan*/  do_vfp_cond_or_thumb () ; 
 int /*<<< orphan*/  do_vfp_nsyn_opcode (char const*) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpu_neon_ext_v1 ; 
 int /*<<< orphan*/  fpu_vfp_ext_v1 ; 
 int /*<<< orphan*/  fpu_vfp_ext_v2 ; 
 TYPE_2__ inst ; 
 int /*<<< orphan*/  is_quarter_float (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 
 struct neon_type_el neon_check_type (int,int,int,int) ; 
 void* neon_dp_fixup (int) ; 
 void* neon_logbits (int) ; 
 int /*<<< orphan*/  neon_move_immediate () ; 
 int neon_qfloat_bits (int) ; 
 int neon_quad (int) ; 
 int neon_select_shape (int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  vfp_or_neon_is_neon (int) ; 

__attribute__((used)) static void
do_neon_mov (void)
{
  enum neon_shape rs = neon_select_shape (NS_RRFF, NS_FFRR, NS_DRR, NS_RRD,
    NS_QQ, NS_DD, NS_QI, NS_DI, NS_SR, NS_RS, NS_FF, NS_FI, NS_RF, NS_FR,
    NS_NULL);
  struct neon_type_el et;
  const char *ldconst = 0;

  switch (rs)
    {
    case NS_DD:  /* case 1/9.  */
      et = neon_check_type (2, rs, N_EQK, N_F64 | N_KEY);
      /* It is not an error here if no type is given.  */
      inst.error = NULL;
      if (et.type == NT_float && et.size == 64)
        {
          do_vfp_nsyn_opcode ("fcpyd");
          break;
        }
      /* fall through.  */

    case NS_QQ:  /* case 0/1.  */
      {
        if (vfp_or_neon_is_neon (NEON_CHECK_CC | NEON_CHECK_ARCH) == FAIL)
          return;
        /* The architecture manual I have doesn't explicitly state which
           value the U bit should have for register->register moves, but
           the equivalent VORR instruction has U = 0, so do that.  */
        inst.instruction = 0x0200110;
        inst.instruction |= LOW4 (inst.operands[0].reg) << 12;
        inst.instruction |= HI1 (inst.operands[0].reg) << 22;
        inst.instruction |= LOW4 (inst.operands[1].reg);
        inst.instruction |= HI1 (inst.operands[1].reg) << 5;
        inst.instruction |= LOW4 (inst.operands[1].reg) << 16;
        inst.instruction |= HI1 (inst.operands[1].reg) << 7;
        inst.instruction |= neon_quad (rs) << 6;

        inst.instruction = neon_dp_fixup (inst.instruction);
      }
      break;
        
    case NS_DI:  /* case 3/11.  */
      et = neon_check_type (2, rs, N_EQK, N_F64 | N_KEY);
      inst.error = NULL;
      if (et.type == NT_float && et.size == 64)
        {
          /* case 11 (fconstd).  */
          ldconst = "fconstd";
          goto encode_fconstd;
        }
      /* fall through.  */

    case NS_QI:  /* case 2/3.  */
      if (vfp_or_neon_is_neon (NEON_CHECK_CC | NEON_CHECK_ARCH) == FAIL)
        return;
      inst.instruction = 0x0800010;
      neon_move_immediate ();
      inst.instruction = neon_dp_fixup (inst.instruction);
      break;
    
    case NS_SR:  /* case 4.  */
      {
        unsigned bcdebits = 0;
        struct neon_type_el et = neon_check_type (2, NS_NULL,
          N_8 | N_16 | N_32 | N_KEY, N_EQK);
        int logsize = neon_logbits (et.size);
        unsigned dn = NEON_SCALAR_REG (inst.operands[0].reg);
        unsigned x = NEON_SCALAR_INDEX (inst.operands[0].reg);

        constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, fpu_vfp_ext_v1),
                    _(BAD_FPU));
        constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, fpu_neon_ext_v1)
                    && et.size != 32, _(BAD_FPU));
        constraint (et.type == NT_invtype, _("bad type for scalar"));
        constraint (x >= 64 / et.size, _("scalar index out of range"));

        switch (et.size)
          {
          case 8:  bcdebits = 0x8; break;
          case 16: bcdebits = 0x1; break;
          case 32: bcdebits = 0x0; break;
          default: ;
          }

        bcdebits |= x << logsize;

        inst.instruction = 0xe000b10;
        do_vfp_cond_or_thumb ();
        inst.instruction |= LOW4 (dn) << 16;
        inst.instruction |= HI1 (dn) << 7;
        inst.instruction |= inst.operands[1].reg << 12;
        inst.instruction |= (bcdebits & 3) << 5;
        inst.instruction |= (bcdebits >> 2) << 21;
      }
      break;
    
    case NS_DRR:  /* case 5 (fmdrr).  */
      constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, fpu_vfp_ext_v2),
                  _(BAD_FPU));

      inst.instruction = 0xc400b10;
      do_vfp_cond_or_thumb ();
      inst.instruction |= LOW4 (inst.operands[0].reg);
      inst.instruction |= HI1 (inst.operands[0].reg) << 5;
      inst.instruction |= inst.operands[1].reg << 12;
      inst.instruction |= inst.operands[2].reg << 16;
      break;
    
    case NS_RS:  /* case 6.  */
      {
        struct neon_type_el et = neon_check_type (2, NS_NULL,
          N_EQK, N_S8 | N_S16 | N_U8 | N_U16 | N_32 | N_KEY);
        unsigned logsize = neon_logbits (et.size);
        unsigned dn = NEON_SCALAR_REG (inst.operands[1].reg);
        unsigned x = NEON_SCALAR_INDEX (inst.operands[1].reg);
        unsigned abcdebits = 0;

        constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, fpu_vfp_ext_v1),
                    _(BAD_FPU));
        constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, fpu_neon_ext_v1)
                    && et.size != 32, _(BAD_FPU));
        constraint (et.type == NT_invtype, _("bad type for scalar"));
        constraint (x >= 64 / et.size, _("scalar index out of range"));

        switch (et.size)
          {
          case 8:  abcdebits = (et.type == NT_signed) ? 0x08 : 0x18; break;
          case 16: abcdebits = (et.type == NT_signed) ? 0x01 : 0x11; break;
          case 32: abcdebits = 0x00; break;
          default: ;
          }

        abcdebits |= x << logsize;
        inst.instruction = 0xe100b10;
        do_vfp_cond_or_thumb ();
        inst.instruction |= LOW4 (dn) << 16;
        inst.instruction |= HI1 (dn) << 7;
        inst.instruction |= inst.operands[0].reg << 12;
        inst.instruction |= (abcdebits & 3) << 5;
        inst.instruction |= (abcdebits >> 2) << 21;
      }
      break;
    
    case NS_RRD:  /* case 7 (fmrrd).  */
      constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, fpu_vfp_ext_v2),
                  _(BAD_FPU));

      inst.instruction = 0xc500b10;
      do_vfp_cond_or_thumb ();
      inst.instruction |= inst.operands[0].reg << 12;
      inst.instruction |= inst.operands[1].reg << 16;
      inst.instruction |= LOW4 (inst.operands[2].reg);
      inst.instruction |= HI1 (inst.operands[2].reg) << 5;
      break;
    
    case NS_FF:  /* case 8 (fcpys).  */
      do_vfp_nsyn_opcode ("fcpys");
      break;
    
    case NS_FI:  /* case 10 (fconsts).  */
      ldconst = "fconsts";
      encode_fconstd:
      if (is_quarter_float (inst.operands[1].imm))
        {
          inst.operands[1].imm = neon_qfloat_bits (inst.operands[1].imm);
          do_vfp_nsyn_opcode (ldconst);
        }
      else
        first_error (_("immediate out of range"));
      break;
    
    case NS_RF:  /* case 12 (fmrs).  */
      do_vfp_nsyn_opcode ("fmrs");
      break;
    
    case NS_FR:  /* case 13 (fmsr).  */
      do_vfp_nsyn_opcode ("fmsr");
      break;
    
    /* The encoders for the fmrrs and fmsrr instructions expect three operands
       (one of which is a list), but we have parsed four.  Do some fiddling to
       make the operands what do_vfp_reg2_from_sp2 and do_vfp_sp2_from_reg2
       expect.  */
    case NS_RRFF:  /* case 14 (fmrrs).  */
      constraint (inst.operands[3].reg != inst.operands[2].reg + 1,
                  _("VFP registers must be adjacent"));
      inst.operands[2].imm = 2;
      memset (&inst.operands[3], '\0', sizeof (inst.operands[3]));
      do_vfp_nsyn_opcode ("fmrrs");
      break;
    
    case NS_FFRR:  /* case 15 (fmsrr).  */
      constraint (inst.operands[1].reg != inst.operands[0].reg + 1,
                  _("VFP registers must be adjacent"));
      inst.operands[1] = inst.operands[2];
      inst.operands[2] = inst.operands[3];
      inst.operands[0].imm = 2;
      memset (&inst.operands[3], '\0', sizeof (inst.operands[3]));
      do_vfp_nsyn_opcode ("fmsrr");
      break;
    
    default:
      abort ();
    }
}