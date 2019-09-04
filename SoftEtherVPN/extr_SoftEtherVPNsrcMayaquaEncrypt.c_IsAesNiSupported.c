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

bool IsAesNiSupported()
{
	bool supported = false;

	// Unfortunately OpenSSL doesn't provide a function to do it
#ifdef _MSC_VER
	int regs[4]; // EAX, EBX, ECX, EDX
	__cpuid(regs, 1);
	supported = (regs[2] >> 25) & 1;
#else // _MSC_VER
	#if defined(CPU_FEATURES_ARCH_X86)
		const X86Features features = GetX86Info().features;
		supported = features.aes;
	#elif defined(CPU_FEATURES_ARCH_ARM)
		const ArmFeatures features = GetArmInfo().features;
		supported = features.aes;
	#elif defined(CPU_FEATURES_ARCH_AARCH64)
		const Aarch64Features features = GetAarch64Info().features;
		supported = features.aes;
	#elif defined(CPU_FEATURES_ARCH_MIPS)
		//const MipsFeatures features = GetMipsInfo().features;  // no features.aes
	#elif defined(CPU_FEATURES_ARCH_PPC)
		//const PPCFeatures features = GetPPCInfo().features;  // no features.aes
	#endif
#endif // _MSC_VER

	return supported;
}