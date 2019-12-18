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
#define  EM_386 207 
#define  EM_486 206 
#define  EM_68HC05 205 
#define  EM_68HC08 204 
#define  EM_68HC11 203 
#define  EM_68HC16 202 
#define  EM_68K 201 
#define  EM_860 200 
#define  EM_960 199 
#define  EM_ALPHA 198 
#define  EM_ALTERA_NIOS2 197 
#define  EM_ARM 196 
#define  EM_AVR 195 
#define  EM_AVR_OLD 194 
#define  EM_BLACKFIN 193 
#define  EM_CRIS 192 
#define  EM_CRX 191 
#define  EM_CYGNUS_D10V 190 
#define  EM_CYGNUS_D30V 189 
#define  EM_CYGNUS_FR30 188 
#define  EM_CYGNUS_FRV 187 
#define  EM_CYGNUS_M32R 186 
#define  EM_CYGNUS_MEP 185 
#define  EM_CYGNUS_MN10200 184 
#define  EM_CYGNUS_MN10300 183 
#define  EM_CYGNUS_V850 182 
#define  EM_D10V 181 
#define  EM_D30V 180 
#define  EM_DLX 179 
#define  EM_FR30 178 
#define  EM_FX66 177 
#define  EM_H8S 176 
#define  EM_H8_300 175 
#define  EM_H8_300H 174 
#define  EM_IA_64 173 
#define  EM_IP2K 172 
#define  EM_IP2K_OLD 171 
#define  EM_IQ2000 170 
#define  EM_M32C 169 
#define  EM_M32R 168 
#define  EM_MCORE 167 
#define  EM_ME16 166 
#define  EM_MIPS 165 
#define  EM_MIPS_RS3_LE 164 
#define  EM_MMA 163 
#define  EM_MMIX 162 
#define  EM_MN10200 161 
#define  EM_MN10300 160 
#define  EM_MSP430 159 
#define  EM_MSP430_OLD 158 
#define  EM_MT 157 
#define  EM_NCPU 156 
#define  EM_NDR1 155 
#define  EM_NIOS32 154 
#define  EM_OPENRISC 153 
#define  EM_OR32 152 
#define  EM_PCP 151 
#define  EM_PPC 150 
#define  EM_PPC64 149 
#define  EM_S390 148 
#define  EM_S390_OLD 147 
#define  EM_SCORE 146 
#define  EM_SH 145 
#define  EM_SPARC 144 
#define  EM_SPARC32PLUS 143 
#define  EM_SPARCV9 142 
#define  EM_SPU 141 
#define  EM_ST100 140 
#define  EM_ST19 139 
#define  EM_ST7 138 
#define  EM_ST9PLUS 137 
#define  EM_STARCORE 136 
#define  EM_SVX 135 
#define  EM_TINYJ 134 
#define  EM_V850 133 
#define  EM_VAX 132 
#define  EM_X86_64 131 
#define  EM_XSTORMY16 130 
#define  EM_XTENSA 129 
#define  EM_XTENSA_OLD 128 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  warn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
guess_is_rela (unsigned long e_machine)
{
  switch (e_machine)
    {
      /* Targets that use REL relocations.  */
    case EM_386:
    case EM_486:
    case EM_960:
    case EM_ARM:
    case EM_D10V:
    case EM_CYGNUS_D10V:
    case EM_DLX:
    case EM_MIPS:
    case EM_MIPS_RS3_LE:
    case EM_CYGNUS_M32R:
    case EM_OPENRISC:
    case EM_OR32:
    case EM_SCORE:
      return FALSE;

      /* Targets that use RELA relocations.  */
    case EM_68K:
    case EM_860:
    case EM_ALPHA:
    case EM_ALTERA_NIOS2:
    case EM_AVR:
    case EM_AVR_OLD:
    case EM_BLACKFIN:
    case EM_CRIS:
    case EM_CRX:
    case EM_D30V:
    case EM_CYGNUS_D30V:
    case EM_FR30:
    case EM_CYGNUS_FR30:
    case EM_CYGNUS_FRV:
    case EM_H8S:
    case EM_H8_300:
    case EM_H8_300H:
    case EM_IA_64:
    case EM_IP2K:
    case EM_IP2K_OLD:
    case EM_IQ2000:
    case EM_M32C:
    case EM_M32R:
    case EM_MCORE:
    case EM_CYGNUS_MEP:
    case EM_MMIX:
    case EM_MN10200:
    case EM_CYGNUS_MN10200:
    case EM_MN10300:
    case EM_CYGNUS_MN10300:
    case EM_MSP430:
    case EM_MSP430_OLD:
    case EM_MT:
    case EM_NIOS32:
    case EM_PPC64:
    case EM_PPC:
    case EM_S390:
    case EM_S390_OLD:
    case EM_SH:
    case EM_SPARC:
    case EM_SPARC32PLUS:
    case EM_SPARCV9:
    case EM_SPU:
    case EM_V850:
    case EM_CYGNUS_V850:
    case EM_VAX:
    case EM_X86_64:
    case EM_XSTORMY16:
    case EM_XTENSA:
    case EM_XTENSA_OLD:
      return TRUE;

    case EM_68HC05:
    case EM_68HC08:
    case EM_68HC11:
    case EM_68HC16:
    case EM_FX66:
    case EM_ME16:
    case EM_MMA:
    case EM_NCPU:
    case EM_NDR1:
    case EM_PCP:
    case EM_ST100:
    case EM_ST19:
    case EM_ST7:
    case EM_ST9PLUS:
    case EM_STARCORE:
    case EM_SVX:
    case EM_TINYJ:
    default:
      warn (_("Don't know about relocations on this machine architecture\n"));
      return FALSE;
    }
}