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
struct elf32_hdr {scalar_t__ e_machine; int e_flags; } ;

/* Variables and functions */
#define  EF_FRV_CPU_FR300 140 
#define  EF_FRV_CPU_FR400 139 
#define  EF_FRV_CPU_FR450 138 
#define  EF_FRV_CPU_FR500 137 
#define  EF_FRV_CPU_FR550 136 
#define  EF_FRV_CPU_GENERIC 135 
 int EF_FRV_CPU_MASK ; 
#define  EF_FRV_CPU_SIMPLE 134 
#define  EF_FRV_CPU_TOMCAT 133 
#define  EF_FRV_FPR32 132 
#define  EF_FRV_FPR64 131 
 int EF_FRV_FPR_MASK ; 
#define  EF_FRV_FPR_NONE 130 
#define  EF_FRV_GPR32 129 
#define  EF_FRV_GPR64 128 
 int EF_FRV_GPR_MASK ; 
 int EF_FRV_MULADD ; 
 scalar_t__ EM_FRV ; 
 unsigned long HSR0_FRN ; 
 unsigned long HSR0_FRN_32 ; 
 unsigned long HSR0_GRN ; 
 unsigned long HSR0_GRN_32 ; 
 scalar_t__ PSR_IMPLE (unsigned long) ; 
 scalar_t__ PSR_IMPLE_FR401 ; 
 scalar_t__ PSR_IMPLE_FR405 ; 
 scalar_t__ PSR_IMPLE_FR451 ; 
 scalar_t__ PSR_IMPLE_FR501 ; 
 scalar_t__ PSR_IMPLE_FR551 ; 
 unsigned long __get_HSR (int /*<<< orphan*/ ) ; 
 unsigned long __get_PSR () ; 

int elf_check_arch(const struct elf32_hdr *hdr)
{
	unsigned long hsr0 = __get_HSR(0);
	unsigned long psr = __get_PSR();

	if (hdr->e_machine != EM_FRV)
		return 0;

	switch (hdr->e_flags & EF_FRV_GPR_MASK) {
	case EF_FRV_GPR64:
		if ((hsr0 & HSR0_GRN) == HSR0_GRN_32)
			return 0;
	case EF_FRV_GPR32:
	case 0:
		break;
	default:
		return 0;
	}

	switch (hdr->e_flags & EF_FRV_FPR_MASK) {
	case EF_FRV_FPR64:
		if ((hsr0 & HSR0_FRN) == HSR0_FRN_32)
			return 0;
	case EF_FRV_FPR32:
	case EF_FRV_FPR_NONE:
	case 0:
		break;
	default:
		return 0;
	}

	if ((hdr->e_flags & EF_FRV_MULADD) == EF_FRV_MULADD)
		if (PSR_IMPLE(psr) != PSR_IMPLE_FR405 &&
		    PSR_IMPLE(psr) != PSR_IMPLE_FR451)
			return 0;

	switch (hdr->e_flags & EF_FRV_CPU_MASK) {
	case EF_FRV_CPU_GENERIC:
		break;
	case EF_FRV_CPU_FR300:
	case EF_FRV_CPU_SIMPLE:
	case EF_FRV_CPU_TOMCAT:
	default:
		return 0;
	case EF_FRV_CPU_FR400:
		if (PSR_IMPLE(psr) != PSR_IMPLE_FR401 &&
		    PSR_IMPLE(psr) != PSR_IMPLE_FR405 &&
		    PSR_IMPLE(psr) != PSR_IMPLE_FR451 &&
		    PSR_IMPLE(psr) != PSR_IMPLE_FR551)
			return 0;
		break;
	case EF_FRV_CPU_FR450:
		if (PSR_IMPLE(psr) != PSR_IMPLE_FR451)
			return 0;
		break;
	case EF_FRV_CPU_FR500:
		if (PSR_IMPLE(psr) != PSR_IMPLE_FR501)
			return 0;
		break;
	case EF_FRV_CPU_FR550:
		if (PSR_IMPLE(psr) != PSR_IMPLE_FR551)
			return 0;
		break;
	}

	return 1;
}