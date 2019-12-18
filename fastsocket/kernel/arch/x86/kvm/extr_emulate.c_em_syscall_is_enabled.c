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
typedef  scalar_t__ u32 ;
struct x86_emulate_ops {scalar_t__ (* get_cpuid ) (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ;} ;
struct x86_emulate_ctxt {scalar_t__ mode; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 scalar_t__ X86EMUL_CPUID_VENDOR_AMDisbetterI_ebx ; 
 scalar_t__ X86EMUL_CPUID_VENDOR_AMDisbetterI_ecx ; 
 scalar_t__ X86EMUL_CPUID_VENDOR_AMDisbetterI_edx ; 
 scalar_t__ X86EMUL_CPUID_VENDOR_AuthenticAMD_ebx ; 
 scalar_t__ X86EMUL_CPUID_VENDOR_AuthenticAMD_ecx ; 
 scalar_t__ X86EMUL_CPUID_VENDOR_AuthenticAMD_edx ; 
 scalar_t__ X86EMUL_CPUID_VENDOR_GenuineIntel_ebx ; 
 scalar_t__ X86EMUL_CPUID_VENDOR_GenuineIntel_ecx ; 
 scalar_t__ X86EMUL_CPUID_VENDOR_GenuineIntel_edx ; 
 scalar_t__ X86EMUL_MODE_PROT64 ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static bool em_syscall_is_enabled(struct x86_emulate_ctxt *ctxt,
				  struct x86_emulate_ops *ops)
{
	u32 eax, ebx, ecx, edx;

	/*
 	 * syscall should always be enabled in longmode - so only become
	 * vendor specific (cpuid) if other modes are active...
 	 */
	if (ctxt->mode == X86EMUL_MODE_PROT64)
		return true;

	eax = 0x00000000;
	ecx = 0x00000000;
	if (ops->get_cpuid(ctxt->vcpu, &eax, &ebx, &ecx, &edx)) {
		/*
	 	 * Intel ("GenuineIntel")
	 	 * remark: Intel CPUs only support "syscall" in 64bit
	 	 * longmode. Also an 64bit guest with a
	 	 * 32bit compat-app running will #UD !! While this
	 	 * behaviour can be fixed (by emulating) into AMD
	 	 * response - CPUs of AMD can't behave like Intel.
	 	 */
		if (ebx == X86EMUL_CPUID_VENDOR_GenuineIntel_ebx &&
		    ecx == X86EMUL_CPUID_VENDOR_GenuineIntel_ecx &&
		    edx == X86EMUL_CPUID_VENDOR_GenuineIntel_edx)
			return false;

		/* AMD ("AuthenticAMD") */
    		if (ebx == X86EMUL_CPUID_VENDOR_AuthenticAMD_ebx &&
		    ecx == X86EMUL_CPUID_VENDOR_AuthenticAMD_ecx &&
		    edx == X86EMUL_CPUID_VENDOR_AuthenticAMD_edx)
			return true;

		/* AMD ("AMDisbetter!") */
		if (ebx == X86EMUL_CPUID_VENDOR_AMDisbetterI_ebx &&
		    ecx == X86EMUL_CPUID_VENDOR_AMDisbetterI_ecx &&
		    edx == X86EMUL_CPUID_VENDOR_AMDisbetterI_edx)
			return true;
	}

	/* default: (not Intel, not AMD), apply Intel's stricter rules... */
	return false;
}