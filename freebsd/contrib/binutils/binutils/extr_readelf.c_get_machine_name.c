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
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
#define  EM_386 230 
#define  EM_486 229 
#define  EM_68HC05 228 
#define  EM_68HC08 227 
#define  EM_68HC11 226 
#define  EM_68HC12 225 
#define  EM_68HC16 224 
#define  EM_68K 223 
#define  EM_860 222 
#define  EM_88K 221 
#define  EM_960 220 
#define  EM_ALPHA 219 
#define  EM_ALTERA_NIOS2 218 
#define  EM_ARC 217 
#define  EM_ARM 216 
#define  EM_AVR 215 
#define  EM_AVR_OLD 214 
#define  EM_BLACKFIN 213 
#define  EM_COLDFIRE 212 
#define  EM_CRIS 211 
#define  EM_CRX 210 
#define  EM_CYGNUS_D10V 209 
#define  EM_CYGNUS_D30V 208 
#define  EM_CYGNUS_FR30 207 
#define  EM_CYGNUS_FRV 206 
#define  EM_CYGNUS_M32R 205 
#define  EM_CYGNUS_MEP 204 
#define  EM_CYGNUS_MN10200 203 
#define  EM_CYGNUS_MN10300 202 
#define  EM_CYGNUS_V850 201 
#define  EM_D10V 200 
#define  EM_D30V 199 
#define  EM_DLX 198 
#define  EM_FIREPATH 197 
#define  EM_FR20 196 
#define  EM_FR30 195 
#define  EM_FX66 194 
#define  EM_H8S 193 
#define  EM_H8_300 192 
#define  EM_H8_300H 191 
#define  EM_H8_500 190 
#define  EM_HUANY 189 
#define  EM_IA_64 188 
#define  EM_IP2K 187 
#define  EM_IP2K_OLD 186 
#define  EM_IQ2000 185 
#define  EM_JAVELIN 184 
#define  EM_M32 183 
#define  EM_M32C 182 
#define  EM_M32R 181 
#define  EM_MCORE 180 
#define  EM_ME16 179 
#define  EM_MIPS 178 
#define  EM_MIPS_RS3_LE 177 
#define  EM_MIPS_X 176 
#define  EM_MMA 175 
#define  EM_MMIX 174 
#define  EM_MN10200 173 
#define  EM_MN10300 172 
#define  EM_MT 171 
#define  EM_NCPU 170 
#define  EM_NDR1 169 
#define  EM_NIOS32 168 
#define  EM_NONE 167 
#define  EM_OLD_ALPHA 166 
#define  EM_OLD_SPARCV9 165 
#define  EM_OPENRISC 164 
#define  EM_OR32 163 
#define  EM_PARISC 162 
#define  EM_PCP 161 
#define  EM_PJ 160 
#define  EM_PJ_OLD 159 
#define  EM_PPC 158 
#define  EM_PPC64 157 
#define  EM_PPC_OLD 156 
#define  EM_PRISM 155 
#define  EM_RH32 154 
#define  EM_S370 153 
#define  EM_S390 152 
#define  EM_S390_OLD 151 
#define  EM_SCORE 150 
#define  EM_SH 149 
#define  EM_SPARC 148 
#define  EM_SPARC32PLUS 147 
#define  EM_SPARCV9 146 
#define  EM_SPU 145 
#define  EM_ST100 144 
#define  EM_ST19 143 
#define  EM_ST7 142 
#define  EM_ST9PLUS 141 
#define  EM_STARCORE 140 
#define  EM_SVX 139 
#define  EM_TINYJ 138 
#define  EM_TRICORE 137 
#define  EM_V800 136 
#define  EM_V850 135 
#define  EM_VAX 134 
#define  EM_X86_64 133 
#define  EM_XC16X 132 
#define  EM_XSTORMY16 131 
#define  EM_XTENSA 130 
#define  EM_XTENSA_OLD 129 
#define  EM_ZSP 128 
 char* _ (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static char *
get_machine_name (unsigned e_machine)
{
  static char buff[64]; /* XXX */

  switch (e_machine)
    {
    case EM_NONE:		return _("None");
    case EM_M32:		return "WE32100";
    case EM_SPARC:		return "Sparc";
    case EM_SPU:		return "SPU";
    case EM_386:		return "Intel 80386";
    case EM_68K:		return "MC68000";
    case EM_88K:		return "MC88000";
    case EM_486:		return "Intel 80486";
    case EM_860:		return "Intel 80860";
    case EM_MIPS:		return "MIPS R3000";
    case EM_S370:		return "IBM System/370";
    case EM_MIPS_RS3_LE:	return "MIPS R4000 big-endian";
    case EM_OLD_SPARCV9:	return "Sparc v9 (old)";
    case EM_PARISC:		return "HPPA";
    case EM_PPC_OLD:		return "Power PC (old)";
    case EM_SPARC32PLUS:	return "Sparc v8+" ;
    case EM_960:		return "Intel 90860";
    case EM_PPC:		return "PowerPC";
    case EM_PPC64:		return "PowerPC64";
    case EM_V800:		return "NEC V800";
    case EM_FR20:		return "Fujitsu FR20";
    case EM_RH32:		return "TRW RH32";
    case EM_MCORE:		return "MCORE";
    case EM_ARM:		return "ARM";
    case EM_OLD_ALPHA:		return "Digital Alpha (old)";
    case EM_SH:			return "Renesas / SuperH SH";
    case EM_SPARCV9:		return "Sparc v9";
    case EM_TRICORE:		return "Siemens Tricore";
    case EM_ARC:		return "ARC";
    case EM_H8_300:		return "Renesas H8/300";
    case EM_H8_300H:		return "Renesas H8/300H";
    case EM_H8S:		return "Renesas H8S";
    case EM_H8_500:		return "Renesas H8/500";
    case EM_IA_64:		return "Intel IA-64";
    case EM_MIPS_X:		return "Stanford MIPS-X";
    case EM_COLDFIRE:		return "Motorola Coldfire";
    case EM_68HC12:		return "Motorola M68HC12";
    case EM_ALPHA:		return "Alpha";
    case EM_CYGNUS_D10V:
    case EM_D10V:		return "d10v";
    case EM_CYGNUS_D30V:
    case EM_D30V:		return "d30v";
    case EM_CYGNUS_M32R:
    case EM_M32R:		return "Renesas M32R (formerly Mitsubishi M32r)";
    case EM_CYGNUS_V850:
    case EM_V850:		return "NEC v850";
    case EM_CYGNUS_MN10300:
    case EM_MN10300:		return "mn10300";
    case EM_CYGNUS_MN10200:
    case EM_MN10200:		return "mn10200";
    case EM_CYGNUS_FR30:
    case EM_FR30:		return "Fujitsu FR30";
    case EM_CYGNUS_FRV:		return "Fujitsu FR-V";
    case EM_PJ_OLD:
    case EM_PJ:			return "picoJava";
    case EM_MMA:		return "Fujitsu Multimedia Accelerator";
    case EM_PCP:		return "Siemens PCP";
    case EM_NCPU:		return "Sony nCPU embedded RISC processor";
    case EM_NDR1:		return "Denso NDR1 microprocesspr";
    case EM_STARCORE:		return "Motorola Star*Core processor";
    case EM_ME16:		return "Toyota ME16 processor";
    case EM_ST100:		return "STMicroelectronics ST100 processor";
    case EM_TINYJ:		return "Advanced Logic Corp. TinyJ embedded processor";
    case EM_FX66:		return "Siemens FX66 microcontroller";
    case EM_ST9PLUS:		return "STMicroelectronics ST9+ 8/16 bit microcontroller";
    case EM_ST7:		return "STMicroelectronics ST7 8-bit microcontroller";
    case EM_68HC16:		return "Motorola MC68HC16 Microcontroller";
    case EM_68HC11:		return "Motorola MC68HC11 Microcontroller";
    case EM_68HC08:		return "Motorola MC68HC08 Microcontroller";
    case EM_68HC05:		return "Motorola MC68HC05 Microcontroller";
    case EM_SVX:		return "Silicon Graphics SVx";
    case EM_ST19:		return "STMicroelectronics ST19 8-bit microcontroller";
    case EM_VAX:		return "Digital VAX";
    case EM_AVR_OLD:
    case EM_AVR:		return "Atmel AVR 8-bit microcontroller";
    case EM_CRIS:		return "Axis Communications 32-bit embedded processor";
    case EM_JAVELIN:		return "Infineon Technologies 32-bit embedded cpu";
    case EM_FIREPATH:		return "Element 14 64-bit DSP processor";
    case EM_ZSP:		return "LSI Logic's 16-bit DSP processor";
    case EM_MMIX:		return "Donald Knuth's educational 64-bit processor";
    case EM_HUANY:		return "Harvard Universitys's machine-independent object format";
    case EM_PRISM:		return "Vitesse Prism";
    case EM_X86_64:		return "Advanced Micro Devices X86-64";
    case EM_S390_OLD:
    case EM_S390:		return "IBM S/390";
    case EM_SCORE:		return "SUNPLUS S+Core";
    case EM_XSTORMY16:		return "Sanyo Xstormy16 CPU core";
    case EM_OPENRISC:
    case EM_OR32:		return "OpenRISC";
    case EM_CRX:		return "National Semiconductor CRX microprocessor";
    case EM_DLX:		return "OpenDLX";
    case EM_IP2K_OLD:
    case EM_IP2K:		return "Ubicom IP2xxx 8-bit microcontrollers";
    case EM_IQ2000:       	return "Vitesse IQ2000";
    case EM_XTENSA_OLD:
    case EM_XTENSA:		return "Tensilica Xtensa Processor";
    case EM_M32C:	        return "Renesas M32c";
    case EM_MT:                 return "Morpho Techologies MT processor";
    case EM_BLACKFIN:		return "Analog Devices Blackfin";
    case EM_NIOS32:		return "Altera Nios";
    case EM_ALTERA_NIOS2:	return "Altera Nios II";
    case EM_XC16X:		return "Infineon Technologies xc16x";
    case EM_CYGNUS_MEP:         return "Toshiba MeP Media Engine";
    default:
      snprintf (buff, sizeof (buff), _("<unknown>: 0x%x"), e_machine);
      return buff;
    }
}