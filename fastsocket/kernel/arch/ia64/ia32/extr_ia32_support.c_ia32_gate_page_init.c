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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __IA32_NR_rt_sigreturn ; 
 int __IA32_NR_sigreturn ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia32_gate_page ; 
 unsigned long* page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ia32_gate_page_init(void)
{
	unsigned long *sr;

	ia32_gate_page = alloc_page(GFP_KERNEL);
	sr = page_address(ia32_gate_page);
	/* This is popl %eax ; movl $,%eax ; int $0x80 */
	*sr++ = 0xb858 | (__IA32_NR_sigreturn << 16) | (0x80cdUL << 48);

	/* This is movl $,%eax ; int $0x80 */
	*sr = 0xb8 | (__IA32_NR_rt_sigreturn << 8) | (0x80cdUL << 40);
}