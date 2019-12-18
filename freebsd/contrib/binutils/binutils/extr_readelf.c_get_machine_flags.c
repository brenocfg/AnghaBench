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

/* Variables and functions */
#define  EFA_PARISC_1_0 210 
#define  EFA_PARISC_1_1 209 
#define  EFA_PARISC_2_0 208 
#define  EF_FRV_CPU_FR300 207 
#define  EF_FRV_CPU_FR400 206 
#define  EF_FRV_CPU_FR405 205 
#define  EF_FRV_CPU_FR450 204 
#define  EF_FRV_CPU_FR500 203 
#define  EF_FRV_CPU_FR550 202 
#define  EF_FRV_CPU_GENERIC 201 
 unsigned int EF_FRV_CPU_MASK ; 
#define  EF_FRV_CPU_SIMPLE 200 
#define  EF_FRV_CPU_TOMCAT 199 
 unsigned int EF_IA_64_ABI64 ; 
 unsigned int EF_IA_64_ABSOLUTE ; 
 unsigned int EF_IA_64_CONS_GP ; 
 unsigned int EF_IA_64_NOFUNCDESC_CONS_GP ; 
 unsigned int EF_IA_64_REDUCEDFP ; 
 unsigned int EF_M32R_ARCH ; 
 unsigned int EF_M68K_ARCH_MASK ; 
#define  EF_M68K_CF_EMAC 198 
 unsigned int EF_M68K_CF_FLOAT ; 
#define  EF_M68K_CF_ISA_A 197 
#define  EF_M68K_CF_ISA_A_NODIV 196 
#define  EF_M68K_CF_ISA_A_PLUS 195 
#define  EF_M68K_CF_ISA_B 194 
#define  EF_M68K_CF_ISA_B_NOUSP 193 
 unsigned int EF_M68K_CF_ISA_MASK ; 
#define  EF_M68K_CF_MAC 192 
 unsigned int EF_M68K_CF_MAC_MASK ; 
 unsigned int EF_M68K_CPU32 ; 
 unsigned int EF_M68K_FIDO ; 
 unsigned int EF_M68K_M68000 ; 
 unsigned int EF_MIPS_32BITMODE ; 
 unsigned int EF_MIPS_ABI ; 
 unsigned int EF_MIPS_ABI2 ; 
 unsigned int EF_MIPS_ARCH ; 
 unsigned int EF_MIPS_ARCH_ASE_M16 ; 
 unsigned int EF_MIPS_ARCH_ASE_MDMX ; 
 unsigned int EF_MIPS_CPIC ; 
 unsigned int EF_MIPS_MACH ; 
 unsigned int EF_MIPS_NOREORDER ; 
 unsigned int EF_MIPS_OPTIONS_FIRST ; 
 unsigned int EF_MIPS_PIC ; 
 unsigned int EF_MIPS_UCODE ; 
 unsigned int EF_PARISC_ARCH ; 
 unsigned int EF_PARISC_EXT ; 
 unsigned int EF_PARISC_LAZYSWAP ; 
 unsigned int EF_PARISC_LSB ; 
 unsigned int EF_PARISC_NO_KABP ; 
 unsigned int EF_PARISC_TRAPNIL ; 
 unsigned int EF_PARISC_WIDE ; 
 unsigned int EF_PICOJAVA_GNUCALLS ; 
 unsigned int EF_PICOJAVA_NEWCALLS ; 
 unsigned int EF_PPC_EMB ; 
 unsigned int EF_PPC_RELOCATABLE ; 
 unsigned int EF_PPC_RELOCATABLE_LIB ; 
#define  EF_SH1 191 
#define  EF_SH2 190 
#define  EF_SH2A 189 
#define  EF_SH2A_NOFPU 188 
#define  EF_SH2A_SH3E 187 
#define  EF_SH2A_SH3_NOFPU 186 
#define  EF_SH2A_SH4 185 
#define  EF_SH2A_SH4_NOFPU 184 
#define  EF_SH2E 183 
#define  EF_SH3 182 
#define  EF_SH3E 181 
#define  EF_SH3_DSP 180 
#define  EF_SH3_NOMMU 179 
#define  EF_SH4 178 
#define  EF_SH4A 177 
#define  EF_SH4AL_DSP 176 
#define  EF_SH4A_NOFPU 175 
#define  EF_SH4_NOFPU 174 
#define  EF_SH4_NOMMU_NOFPU 173 
#define  EF_SH5 172 
#define  EF_SH_DSP 171 
 unsigned int EF_SH_MACH_MASK ; 
 unsigned int EF_SPARCV9_MM ; 
 unsigned int EF_SPARCV9_PSO ; 
 unsigned int EF_SPARCV9_RMO ; 
 unsigned int EF_SPARCV9_TSO ; 
 unsigned int EF_SPARC_32PLUS ; 
 unsigned int EF_SPARC_HAL_R1 ; 
 unsigned int EF_SPARC_LEDATA ; 
 unsigned int EF_SPARC_SUN_US1 ; 
 unsigned int EF_SPARC_SUN_US3 ; 
 unsigned int EF_V850_ARCH ; 
 unsigned int EF_VAX_DFLOAT ; 
 unsigned int EF_VAX_GFLOAT ; 
 unsigned int EF_VAX_NONPIC ; 
#define  EM_68K 170 
#define  EM_ARM 169 
#define  EM_CYGNUS_FRV 168 
#define  EM_CYGNUS_M32R 167 
#define  EM_CYGNUS_V850 166 
#define  EM_IA_64 165 
#define  EM_M32R 164 
#define  EM_MIPS 163 
#define  EM_MIPS_RS3_LE 162 
#define  EM_PARISC 161 
#define  EM_PJ 160 
#define  EM_PJ_OLD 159 
#define  EM_PPC 158 
#define  EM_SH 157 
#define  EM_SPARCV9 156 
#define  EM_V850 155 
#define  EM_VAX 154 
 unsigned int E_M32R_ARCH ; 
#define  E_MIPS_ABI_EABI32 153 
#define  E_MIPS_ABI_EABI64 152 
#define  E_MIPS_ABI_O32 151 
#define  E_MIPS_ABI_O64 150 
#define  E_MIPS_ARCH_1 149 
#define  E_MIPS_ARCH_2 148 
#define  E_MIPS_ARCH_3 147 
#define  E_MIPS_ARCH_32 146 
#define  E_MIPS_ARCH_32R2 145 
#define  E_MIPS_ARCH_4 144 
#define  E_MIPS_ARCH_5 143 
#define  E_MIPS_ARCH_64 142 
#define  E_MIPS_ARCH_64R2 141 
#define  E_MIPS_MACH_3900 140 
#define  E_MIPS_MACH_4010 139 
#define  E_MIPS_MACH_4100 138 
#define  E_MIPS_MACH_4111 137 
#define  E_MIPS_MACH_4120 136 
#define  E_MIPS_MACH_4650 135 
#define  E_MIPS_MACH_5400 134 
#define  E_MIPS_MACH_5500 133 
#define  E_MIPS_MACH_9000 132 
#define  E_MIPS_MACH_SB1 131 
#define  E_V850E1_ARCH 130 
#define  E_V850E_ARCH 129 
#define  E_V850_ARCH 128 
 char* _ (char*) ; 
 int /*<<< orphan*/  decode_ARM_machine_flags (unsigned int,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *
get_machine_flags (unsigned e_flags, unsigned e_machine)
{
  static char buf[1024];

  buf[0] = '\0';

  if (e_flags)
    {
      switch (e_machine)
	{
	default:
	  break;

	case EM_ARM:
	  decode_ARM_machine_flags (e_flags, buf);
	  break;

	case EM_CYGNUS_FRV:
	  switch (e_flags & EF_FRV_CPU_MASK)
	    {
	    case EF_FRV_CPU_GENERIC:
	      break;

	    default:
	      strcat (buf, ", fr???");
	      break;

	    case EF_FRV_CPU_FR300:
	      strcat (buf, ", fr300");
	      break;

	    case EF_FRV_CPU_FR400:
	      strcat (buf, ", fr400");
	      break;
	    case EF_FRV_CPU_FR405:
	      strcat (buf, ", fr405");
	      break;

	    case EF_FRV_CPU_FR450:
	      strcat (buf, ", fr450");
	      break;

	    case EF_FRV_CPU_FR500:
	      strcat (buf, ", fr500");
	      break;
	    case EF_FRV_CPU_FR550:
	      strcat (buf, ", fr550");
	      break;

	    case EF_FRV_CPU_SIMPLE:
	      strcat (buf, ", simple");
	      break;
	    case EF_FRV_CPU_TOMCAT:
	      strcat (buf, ", tomcat");
	      break;
	    }
	  break;

	case EM_68K:
	  if ((e_flags & EF_M68K_ARCH_MASK) == EF_M68K_M68000)
	    strcat (buf, ", m68000");
	  else if ((e_flags & EF_M68K_ARCH_MASK) == EF_M68K_CPU32)
	    strcat (buf, ", cpu32");
	  else if ((e_flags & EF_M68K_ARCH_MASK) == EF_M68K_FIDO)
	    strcat (buf, ", fido_a");
	  else
	    {
	      char const *isa = _("unknown");
	      char const *mac = _("unknown mac");
	      char const *additional = NULL;

	      switch (e_flags & EF_M68K_CF_ISA_MASK)
		{
		case EF_M68K_CF_ISA_A_NODIV:
		  isa = "A";
		  additional = ", nodiv";
		  break;
		case EF_M68K_CF_ISA_A:
		  isa = "A";
		  break;
		case EF_M68K_CF_ISA_A_PLUS:
		  isa = "A+";
		  break;
		case EF_M68K_CF_ISA_B_NOUSP:
		  isa = "B";
		  additional = ", nousp";
		  break;
		case EF_M68K_CF_ISA_B:
		  isa = "B";
		  break;
		}
	      strcat (buf, ", cf, isa ");
	      strcat (buf, isa);
	      if (additional)
		strcat (buf, additional);
	      if (e_flags & EF_M68K_CF_FLOAT)
		strcat (buf, ", float");
	      switch (e_flags & EF_M68K_CF_MAC_MASK)
		{
		case 0:
		  mac = NULL;
		  break;
		case EF_M68K_CF_MAC:
		  mac = "mac";
		  break;
		case EF_M68K_CF_EMAC:
		  mac = "emac";
		  break;
		}
	      if (mac)
		{
		  strcat (buf, ", ");
		  strcat (buf, mac);
		}
	    }
	  break;

	case EM_PPC:
	  if (e_flags & EF_PPC_EMB)
	    strcat (buf, ", emb");

	  if (e_flags & EF_PPC_RELOCATABLE)
	    strcat (buf, ", relocatable");

	  if (e_flags & EF_PPC_RELOCATABLE_LIB)
	    strcat (buf, ", relocatable-lib");
	  break;

	case EM_V850:
	case EM_CYGNUS_V850:
	  switch (e_flags & EF_V850_ARCH)
	    {
	    case E_V850E1_ARCH:
	      strcat (buf, ", v850e1");
	      break;
	    case E_V850E_ARCH:
	      strcat (buf, ", v850e");
	      break;
	    case E_V850_ARCH:
	      strcat (buf, ", v850");
	      break;
	    default:
	      strcat (buf, ", unknown v850 architecture variant");
	      break;
	    }
	  break;

	case EM_M32R:
	case EM_CYGNUS_M32R:
	  if ((e_flags & EF_M32R_ARCH) == E_M32R_ARCH)
	    strcat (buf, ", m32r");
	  break;

	case EM_MIPS:
	case EM_MIPS_RS3_LE:
	  if (e_flags & EF_MIPS_NOREORDER)
	    strcat (buf, ", noreorder");

	  if (e_flags & EF_MIPS_PIC)
	    strcat (buf, ", pic");

	  if (e_flags & EF_MIPS_CPIC)
	    strcat (buf, ", cpic");

	  if (e_flags & EF_MIPS_UCODE)
	    strcat (buf, ", ugen_reserved");

	  if (e_flags & EF_MIPS_ABI2)
	    strcat (buf, ", abi2");

	  if (e_flags & EF_MIPS_OPTIONS_FIRST)
	    strcat (buf, ", odk first");

	  if (e_flags & EF_MIPS_32BITMODE)
	    strcat (buf, ", 32bitmode");

	  switch ((e_flags & EF_MIPS_MACH))
	    {
	    case E_MIPS_MACH_3900: strcat (buf, ", 3900"); break;
	    case E_MIPS_MACH_4010: strcat (buf, ", 4010"); break;
	    case E_MIPS_MACH_4100: strcat (buf, ", 4100"); break;
	    case E_MIPS_MACH_4111: strcat (buf, ", 4111"); break;
	    case E_MIPS_MACH_4120: strcat (buf, ", 4120"); break;
	    case E_MIPS_MACH_4650: strcat (buf, ", 4650"); break;
	    case E_MIPS_MACH_5400: strcat (buf, ", 5400"); break;
	    case E_MIPS_MACH_5500: strcat (buf, ", 5500"); break;
	    case E_MIPS_MACH_SB1:  strcat (buf, ", sb1");  break;
	    case E_MIPS_MACH_9000: strcat (buf, ", 9000"); break;
	    case 0:
	    /* We simply ignore the field in this case to avoid confusion:
	       MIPS ELF does not specify EF_MIPS_MACH, it is a GNU
	       extension.  */
	      break;
	    default: strcat (buf, ", unknown CPU"); break;
	    }

	  switch ((e_flags & EF_MIPS_ABI))
	    {
	    case E_MIPS_ABI_O32: strcat (buf, ", o32"); break;
	    case E_MIPS_ABI_O64: strcat (buf, ", o64"); break;
	    case E_MIPS_ABI_EABI32: strcat (buf, ", eabi32"); break;
	    case E_MIPS_ABI_EABI64: strcat (buf, ", eabi64"); break;
	    case 0:
	    /* We simply ignore the field in this case to avoid confusion:
	       MIPS ELF does not specify EF_MIPS_ABI, it is a GNU extension.
	       This means it is likely to be an o32 file, but not for
	       sure.  */
	      break;
	    default: strcat (buf, ", unknown ABI"); break;
	    }

	  if (e_flags & EF_MIPS_ARCH_ASE_MDMX)
	    strcat (buf, ", mdmx");

	  if (e_flags & EF_MIPS_ARCH_ASE_M16)
	    strcat (buf, ", mips16");

	  switch ((e_flags & EF_MIPS_ARCH))
	    {
	    case E_MIPS_ARCH_1: strcat (buf, ", mips1"); break;
	    case E_MIPS_ARCH_2: strcat (buf, ", mips2"); break;
	    case E_MIPS_ARCH_3: strcat (buf, ", mips3"); break;
	    case E_MIPS_ARCH_4: strcat (buf, ", mips4"); break;
	    case E_MIPS_ARCH_5: strcat (buf, ", mips5"); break;
	    case E_MIPS_ARCH_32: strcat (buf, ", mips32"); break;
	    case E_MIPS_ARCH_32R2: strcat (buf, ", mips32r2"); break;
	    case E_MIPS_ARCH_64: strcat (buf, ", mips64"); break;
	    case E_MIPS_ARCH_64R2: strcat (buf, ", mips64r2"); break;
	    default: strcat (buf, ", unknown ISA"); break;
	    }

	  break;

	case EM_SH:
	  switch ((e_flags & EF_SH_MACH_MASK))
	    {
	    case EF_SH1: strcat (buf, ", sh1"); break;
	    case EF_SH2: strcat (buf, ", sh2"); break;
	    case EF_SH3: strcat (buf, ", sh3"); break;
	    case EF_SH_DSP: strcat (buf, ", sh-dsp"); break;
	    case EF_SH3_DSP: strcat (buf, ", sh3-dsp"); break;
	    case EF_SH4AL_DSP: strcat (buf, ", sh4al-dsp"); break;
	    case EF_SH3E: strcat (buf, ", sh3e"); break;
	    case EF_SH4: strcat (buf, ", sh4"); break;
	    case EF_SH5: strcat (buf, ", sh5"); break;
	    case EF_SH2E: strcat (buf, ", sh2e"); break;
	    case EF_SH4A: strcat (buf, ", sh4a"); break;
	    case EF_SH2A: strcat (buf, ", sh2a"); break;
	    case EF_SH4_NOFPU: strcat (buf, ", sh4-nofpu"); break;
	    case EF_SH4A_NOFPU: strcat (buf, ", sh4a-nofpu"); break;
	    case EF_SH2A_NOFPU: strcat (buf, ", sh2a-nofpu"); break;
	    case EF_SH3_NOMMU: strcat (buf, ", sh3-nommu"); break;
	    case EF_SH4_NOMMU_NOFPU: strcat (buf, ", sh4-nommu-nofpu"); break;
	    case EF_SH2A_SH4_NOFPU: strcat (buf, ", sh2a-nofpu-or-sh4-nommu-nofpu"); break;
	    case EF_SH2A_SH3_NOFPU: strcat (buf, ", sh2a-nofpu-or-sh3-nommu"); break;
	    case EF_SH2A_SH4: strcat (buf, ", sh2a-or-sh4"); break;
	    case EF_SH2A_SH3E: strcat (buf, ", sh2a-or-sh3e"); break;
	    default: strcat (buf, ", unknown ISA"); break;
	    }

	  break;

	case EM_SPARCV9:
	  if (e_flags & EF_SPARC_32PLUS)
	    strcat (buf, ", v8+");

	  if (e_flags & EF_SPARC_SUN_US1)
	    strcat (buf, ", ultrasparcI");

	  if (e_flags & EF_SPARC_SUN_US3)
	    strcat (buf, ", ultrasparcIII");

	  if (e_flags & EF_SPARC_HAL_R1)
	    strcat (buf, ", halr1");

	  if (e_flags & EF_SPARC_LEDATA)
	    strcat (buf, ", ledata");

	  if ((e_flags & EF_SPARCV9_MM) == EF_SPARCV9_TSO)
	    strcat (buf, ", tso");

	  if ((e_flags & EF_SPARCV9_MM) == EF_SPARCV9_PSO)
	    strcat (buf, ", pso");

	  if ((e_flags & EF_SPARCV9_MM) == EF_SPARCV9_RMO)
	    strcat (buf, ", rmo");
	  break;

	case EM_PARISC:
	  switch (e_flags & EF_PARISC_ARCH)
	    {
	    case EFA_PARISC_1_0:
	      strcpy (buf, ", PA-RISC 1.0");
	      break;
	    case EFA_PARISC_1_1:
	      strcpy (buf, ", PA-RISC 1.1");
	      break;
	    case EFA_PARISC_2_0:
	      strcpy (buf, ", PA-RISC 2.0");
	      break;
	    default:
	      break;
	    }
	  if (e_flags & EF_PARISC_TRAPNIL)
	    strcat (buf, ", trapnil");
	  if (e_flags & EF_PARISC_EXT)
	    strcat (buf, ", ext");
	  if (e_flags & EF_PARISC_LSB)
	    strcat (buf, ", lsb");
	  if (e_flags & EF_PARISC_WIDE)
	    strcat (buf, ", wide");
	  if (e_flags & EF_PARISC_NO_KABP)
	    strcat (buf, ", no kabp");
	  if (e_flags & EF_PARISC_LAZYSWAP)
	    strcat (buf, ", lazyswap");
	  break;

	case EM_PJ:
	case EM_PJ_OLD:
	  if ((e_flags & EF_PICOJAVA_NEWCALLS) == EF_PICOJAVA_NEWCALLS)
	    strcat (buf, ", new calling convention");

	  if ((e_flags & EF_PICOJAVA_GNUCALLS) == EF_PICOJAVA_GNUCALLS)
	    strcat (buf, ", gnu calling convention");
	  break;

	case EM_IA_64:
	  if ((e_flags & EF_IA_64_ABI64))
	    strcat (buf, ", 64-bit");
	  else
	    strcat (buf, ", 32-bit");
	  if ((e_flags & EF_IA_64_REDUCEDFP))
	    strcat (buf, ", reduced fp model");
	  if ((e_flags & EF_IA_64_NOFUNCDESC_CONS_GP))
	    strcat (buf, ", no function descriptors, constant gp");
	  else if ((e_flags & EF_IA_64_CONS_GP))
	    strcat (buf, ", constant gp");
	  if ((e_flags & EF_IA_64_ABSOLUTE))
	    strcat (buf, ", absolute");
	  break;

	case EM_VAX:
	  if ((e_flags & EF_VAX_NONPIC))
	    strcat (buf, ", non-PIC");
	  if ((e_flags & EF_VAX_DFLOAT))
	    strcat (buf, ", D-Float");
	  if ((e_flags & EF_VAX_GFLOAT))
	    strcat (buf, ", G-Float");
	  break;
	}
    }

  return buf;
}