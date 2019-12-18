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
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int KSYM_SYMBOL_LEN ; 
 int /*<<< orphan*/  kallsyms_lookup (unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 char* kretprobed (char*) ; 
 int trace_seq_printf (struct trace_seq*,char const*,char const*) ; 

__attribute__((used)) static int
seq_print_sym_short(struct trace_seq *s, const char *fmt, unsigned long address)
{
#ifdef CONFIG_KALLSYMS
	char str[KSYM_SYMBOL_LEN];
	const char *name;

	kallsyms_lookup(address, NULL, NULL, NULL, str);

	name = kretprobed(str);

	return trace_seq_printf(s, fmt, name);
#endif
	return 1;
}