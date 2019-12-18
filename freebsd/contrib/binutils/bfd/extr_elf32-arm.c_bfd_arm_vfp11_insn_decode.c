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
typedef  enum bfd_arm_vfp11_pipe { ____Placeholder_bfd_arm_vfp11_pipe } bfd_arm_vfp11_pipe ;
typedef  int bfd_boolean ;

/* Variables and functions */
 int VFP11_BAD ; 
 int VFP11_DS ; 
 int VFP11_FMAC ; 
 int VFP11_LS ; 
 int /*<<< orphan*/  abort () ; 
 void* bfd_arm_vfp11_regno (unsigned int,int,int,int) ; 
 int /*<<< orphan*/  bfd_arm_vfp11_write_mask (unsigned int*,unsigned int) ; 

__attribute__((used)) static enum bfd_arm_vfp11_pipe
bfd_arm_vfp11_insn_decode (unsigned int insn, unsigned int *destmask, int *regs,
                           int *numregs)
{
  enum bfd_arm_vfp11_pipe pipe = VFP11_BAD;
  bfd_boolean is_double = ((insn & 0xf00) == 0xb00) ? 1 : 0;

  if ((insn & 0x0f000e10) == 0x0e000a00)  /* A data-processing insn.  */
    {
      unsigned int pqrs;
      unsigned int fd = bfd_arm_vfp11_regno (insn, is_double, 12, 22);
      unsigned int fm = bfd_arm_vfp11_regno (insn, is_double, 0, 5);

      pqrs = ((insn & 0x00800000) >> 20)
           | ((insn & 0x00300000) >> 19)
           | ((insn & 0x00000040) >> 6);

      switch (pqrs)
        {
        case 0: /* fmac[sd].  */
        case 1: /* fnmac[sd].  */
        case 2: /* fmsc[sd].  */
        case 3: /* fnmsc[sd].  */
          pipe = VFP11_FMAC;
          bfd_arm_vfp11_write_mask (destmask, fd);
          regs[0] = fd;
          regs[1] = bfd_arm_vfp11_regno (insn, is_double, 16, 7);  /* Fn.  */
          regs[2] = fm;
          *numregs = 3;
          break;

        case 4: /* fmul[sd].  */
        case 5: /* fnmul[sd].  */
        case 6: /* fadd[sd].  */
        case 7: /* fsub[sd].  */
          pipe = VFP11_FMAC;
          goto vfp_binop;

        case 8: /* fdiv[sd].  */
          pipe = VFP11_DS;
          vfp_binop:
          bfd_arm_vfp11_write_mask (destmask, fd);
          regs[0] = bfd_arm_vfp11_regno (insn, is_double, 16, 7);   /* Fn.  */
          regs[1] = fm;
          *numregs = 2;
          break;

        case 15: /* extended opcode.  */
          {
            unsigned int extn = ((insn >> 15) & 0x1e)
                              | ((insn >> 7) & 1);

            switch (extn)
              {
              case 0: /* fcpy[sd].  */
              case 1: /* fabs[sd].  */
              case 2: /* fneg[sd].  */
              case 8: /* fcmp[sd].  */
              case 9: /* fcmpe[sd].  */
              case 10: /* fcmpz[sd].  */
              case 11: /* fcmpez[sd].  */
              case 16: /* fuito[sd].  */
              case 17: /* fsito[sd].  */
              case 24: /* ftoui[sd].  */
              case 25: /* ftouiz[sd].  */
              case 26: /* ftosi[sd].  */
              case 27: /* ftosiz[sd].  */
                /* These instructions will not bounce due to underflow.  */
                *numregs = 0;
                pipe = VFP11_FMAC;
                break;

              case 3: /* fsqrt[sd].  */
                /* fsqrt cannot underflow, but it can (perhaps) overwrite
                   registers to cause the erratum in previous instructions.  */
                bfd_arm_vfp11_write_mask (destmask, fd);
                pipe = VFP11_DS;
                break;

              case 15: /* fcvt{ds,sd}.  */
                {
                  int rnum = 0;

                  bfd_arm_vfp11_write_mask (destmask, fd);

		  /* Only FCVTSD can underflow.  */
                  if ((insn & 0x100) != 0)
                    regs[rnum++] = fm;

                  *numregs = rnum;

                  pipe = VFP11_FMAC;
                }
                break;

              default:
                return VFP11_BAD;
              }
          }
          break;

        default:
          return VFP11_BAD;
        }
    }
  /* Two-register transfer.  */
  else if ((insn & 0x0fe00ed0) == 0x0c400a10)
    {
      unsigned int fm = bfd_arm_vfp11_regno (insn, is_double, 0, 5);
      
      if ((insn & 0x100000) == 0)
	{
          if (is_double)
            bfd_arm_vfp11_write_mask (destmask, fm);
          else
            {
              bfd_arm_vfp11_write_mask (destmask, fm);
              bfd_arm_vfp11_write_mask (destmask, fm + 1);
            }
	}

      pipe = VFP11_LS;
    }
  else if ((insn & 0x0e100e00) == 0x0c100a00)  /* A load insn.  */
    {
      int fd = bfd_arm_vfp11_regno (insn, is_double, 12, 22);
      unsigned int puw = ((insn >> 21) & 0x1) | (((insn >> 23) & 3) << 1);
      
      switch (puw)
        {
        case 0: /* Two-reg transfer.  We should catch these above.  */
          abort ();
        
        case 2: /* fldm[sdx].  */
        case 3:
        case 5:
          {
            unsigned int i, offset = insn & 0xff;

            if (is_double)
              offset >>= 1;

            for (i = fd; i < fd + offset; i++)
              bfd_arm_vfp11_write_mask (destmask, i);
          }
          break;
        
        case 4: /* fld[sd].  */
        case 6:
          bfd_arm_vfp11_write_mask (destmask, fd);
          break;
        
        default:
          return VFP11_BAD;
        }

      pipe = VFP11_LS;
    }
  /* Single-register transfer. Note L==0.  */
  else if ((insn & 0x0f100e10) == 0x0e000a10)
    {
      unsigned int opcode = (insn >> 21) & 7;
      unsigned int fn = bfd_arm_vfp11_regno (insn, is_double, 16, 7);

      switch (opcode)
        {
        case 0: /* fmsr/fmdlr.  */
        case 1: /* fmdhr.  */
          /* Mark fmdhr and fmdlr as writing to the whole of the DP
             destination register.  I don't know if this is exactly right,
             but it is the conservative choice.  */
          bfd_arm_vfp11_write_mask (destmask, fn);
          break;

        case 7: /* fmxr.  */
          break;
        }

      pipe = VFP11_LS;
    }

  return pipe;
}