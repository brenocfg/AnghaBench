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
typedef  int /*<<< orphan*/  s_mach ;

/* Variables and functions */
#define  EM_386 219 
#define  EM_68HC05 218 
#define  EM_68HC08 217 
#define  EM_68HC11 216 
#define  EM_68HC12 215 
#define  EM_68HC16 214 
#define  EM_68K 213 
#define  EM_860 212 
#define  EM_88K 211 
#define  EM_960 210 
#define  EM_AARCH64 209 
#define  EM_ARC 208 
#define  EM_ARCA 207 
#define  EM_ARC_A5 206 
#define  EM_ARM 205 
#define  EM_AVR 204 
#define  EM_BLACKFIN 203 
#define  EM_COLDFIRE 202 
#define  EM_CR 201 
#define  EM_CRIS 200 
#define  EM_D10V 199 
#define  EM_D30V 198 
#define  EM_F2MC16 197 
#define  EM_FIREPATH 196 
#define  EM_FR20 195 
#define  EM_FR30 194 
#define  EM_FX66 193 
#define  EM_H8S 192 
#define  EM_H8_300 191 
#define  EM_H8_300H 190 
#define  EM_H8_500 189 
#define  EM_HUANY 188 
#define  EM_IAMCU 187 
#define  EM_IA_64 186 
#define  EM_IP2K 185 
#define  EM_JAVELIN 184 
#define  EM_M32 183 
#define  EM_M32R 182 
#define  EM_MAX 181 
#define  EM_ME16 180 
#define  EM_MIPS 179 
#define  EM_MIPS_RS3_LE 178 
#define  EM_MIPS_X 177 
#define  EM_MMA 176 
#define  EM_MMIX 175 
#define  EM_MN10200 174 
#define  EM_MN10300 173 
#define  EM_MSP430 172 
#define  EM_NCPU 171 
#define  EM_NDR1 170 
#define  EM_NONE 169 
#define  EM_NS32K 168 
#define  EM_OPENRISC 167 
#define  EM_PARISC 166 
#define  EM_PCP 165 
#define  EM_PDSP 164 
#define  EM_PJ 163 
#define  EM_PPC 162 
#define  EM_PPC64 161 
#define  EM_PRISM 160 
#define  EM_RCE 159 
#define  EM_RH32 158 
#define  EM_RISCV 157 
#define  EM_S370 156 
#define  EM_S390 155 
#define  EM_SEP 154 
#define  EM_SE_C33 153 
#define  EM_SH 152 
#define  EM_SNP1K 151 
#define  EM_SPARC 150 
#define  EM_SPARC32PLUS 149 
#define  EM_SPARCV9 148 
#define  EM_ST100 147 
#define  EM_ST19 146 
#define  EM_ST200 145 
#define  EM_ST7 144 
#define  EM_ST9PLUS 143 
#define  EM_STARCORE 142 
#define  EM_SVX 141 
#define  EM_TINYJ 140 
#define  EM_TMM_GPP 139 
#define  EM_TPC 138 
#define  EM_TRICORE 137 
#define  EM_UNICORE 136 
#define  EM_V800 135 
#define  EM_V850 134 
#define  EM_VAX 133 
#define  EM_VIDEOCORE 132 
#define  EM_VPP500 131 
#define  EM_X86_64 130 
#define  EM_XTENSA 129 
#define  EM_ZSP 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
elf_machine(unsigned int mach)
{
	static char s_mach[32];

	switch (mach) {
	case EM_NONE: return "Unknown machine";
	case EM_M32: return "AT&T WE32100";
	case EM_SPARC: return "Sun SPARC";
	case EM_386: return "Intel i386";
	case EM_68K: return "Motorola 68000";
	case EM_IAMCU: return "Intel MCU";
	case EM_88K: return "Motorola 88000";
	case EM_860: return "Intel i860";
	case EM_MIPS: return "MIPS R3000 Big-Endian only";
	case EM_S370: return "IBM System/370";
	case EM_MIPS_RS3_LE: return "MIPS R3000 Little-Endian";
	case EM_PARISC: return "HP PA-RISC";
	case EM_VPP500: return "Fujitsu VPP500";
	case EM_SPARC32PLUS: return "SPARC v8plus";
	case EM_960: return "Intel 80960";
	case EM_PPC: return "PowerPC 32-bit";
	case EM_PPC64: return "PowerPC 64-bit";
	case EM_S390: return "IBM System/390";
	case EM_V800: return "NEC V800";
	case EM_FR20: return "Fujitsu FR20";
	case EM_RH32: return "TRW RH-32";
	case EM_RCE: return "Motorola RCE";
	case EM_ARM: return "ARM";
	case EM_SH: return "Hitachi SH";
	case EM_SPARCV9: return "SPARC v9 64-bit";
	case EM_TRICORE: return "Siemens TriCore embedded processor";
	case EM_ARC: return "Argonaut RISC Core";
	case EM_H8_300: return "Hitachi H8/300";
	case EM_H8_300H: return "Hitachi H8/300H";
	case EM_H8S: return "Hitachi H8S";
	case EM_H8_500: return "Hitachi H8/500";
	case EM_IA_64: return "Intel IA-64 Processor";
	case EM_MIPS_X: return "Stanford MIPS-X";
	case EM_COLDFIRE: return "Motorola ColdFire";
	case EM_68HC12: return "Motorola M68HC12";
	case EM_MMA: return "Fujitsu MMA";
	case EM_PCP: return "Siemens PCP";
	case EM_NCPU: return "Sony nCPU";
	case EM_NDR1: return "Denso NDR1 microprocessor";
	case EM_STARCORE: return "Motorola Star*Core processor";
	case EM_ME16: return "Toyota ME16 processor";
	case EM_ST100: return "STMicroelectronics ST100 processor";
	case EM_TINYJ: return "Advanced Logic Corp. TinyJ processor";
	case EM_X86_64: return "Advanced Micro Devices x86-64";
	case EM_PDSP: return "Sony DSP Processor";
	case EM_FX66: return "Siemens FX66 microcontroller";
	case EM_ST9PLUS: return "STMicroelectronics ST9+ 8/16 microcontroller";
	case EM_ST7: return "STmicroelectronics ST7 8-bit microcontroller";
	case EM_68HC16: return "Motorola MC68HC16 microcontroller";
	case EM_68HC11: return "Motorola MC68HC11 microcontroller";
	case EM_68HC08: return "Motorola MC68HC08 microcontroller";
	case EM_68HC05: return "Motorola MC68HC05 microcontroller";
	case EM_SVX: return "Silicon Graphics SVx";
	case EM_ST19: return "STMicroelectronics ST19 8-bit mc";
	case EM_VAX: return "Digital VAX";
	case EM_CRIS: return "Axis Communications 32-bit embedded processor";
	case EM_JAVELIN: return "Infineon Tech. 32bit embedded processor";
	case EM_FIREPATH: return "Element 14 64-bit DSP Processor";
	case EM_ZSP: return "LSI Logic 16-bit DSP Processor";
	case EM_MMIX: return "Donald Knuth's educational 64-bit proc";
	case EM_HUANY: return "Harvard University MI object files";
	case EM_PRISM: return "SiTera Prism";
	case EM_AVR: return "Atmel AVR 8-bit microcontroller";
	case EM_FR30: return "Fujitsu FR30";
	case EM_D10V: return "Mitsubishi D10V";
	case EM_D30V: return "Mitsubishi D30V";
	case EM_V850: return "NEC v850";
	case EM_M32R: return "Mitsubishi M32R";
	case EM_MN10300: return "Matsushita MN10300";
	case EM_MN10200: return "Matsushita MN10200";
	case EM_PJ: return "picoJava";
	case EM_OPENRISC: return "OpenRISC 32-bit embedded processor";
	case EM_ARC_A5: return "ARC Cores Tangent-A5";
	case EM_XTENSA: return "Tensilica Xtensa Architecture";
	case EM_VIDEOCORE: return "Alphamosaic VideoCore processor";
	case EM_TMM_GPP: return "Thompson Multimedia General Purpose Processor";
	case EM_NS32K: return "National Semiconductor 32000 series";
	case EM_TPC: return "Tenor Network TPC processor";
	case EM_SNP1K: return "Trebia SNP 1000 processor";
	case EM_ST200: return "STMicroelectronics ST200 microcontroller";
	case EM_IP2K: return "Ubicom IP2xxx microcontroller family";
	case EM_MAX: return "MAX Processor";
	case EM_CR: return "National Semiconductor CompactRISC microprocessor";
	case EM_F2MC16: return "Fujitsu F2MC16";
	case EM_MSP430: return "TI embedded microcontroller msp430";
	case EM_BLACKFIN: return "Analog Devices Blackfin (DSP) processor";
	case EM_SE_C33: return "S1C33 Family of Seiko Epson processors";
	case EM_SEP: return "Sharp embedded microprocessor";
	case EM_ARCA: return "Arca RISC Microprocessor";
	case EM_UNICORE: return "Microprocessor series from PKU-Unity Ltd";
	case EM_AARCH64: return "AArch64";
	case EM_RISCV: return "RISC-V";
	default:
		snprintf(s_mach, sizeof(s_mach), "<unknown: %#x>", mach);
		return (s_mach);
	}

}