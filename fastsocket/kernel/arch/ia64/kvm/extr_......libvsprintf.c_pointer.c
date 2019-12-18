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
struct va_format {int /*<<< orphan*/ * va; int /*<<< orphan*/  fmt; } ;
struct printf_spec {int field_width; int base; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  SMALL ; 
 int /*<<< orphan*/  ZEROPAD ; 
 int /*<<< orphan*/  current ; 
 void* dereference_function_descriptor (void*) ; 
 int /*<<< orphan*/  has_capability_noaudit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_irq () ; 
 int /*<<< orphan*/  in_nmi () ; 
 int /*<<< orphan*/  in_softirq () ; 
 char* ip4_addr_string (char*,char*,void*,struct printf_spec,char const*) ; 
 char* ip6_addr_string (char*,char*,void*,struct printf_spec,char const*) ; 
 int kptr_restrict ; 
 char* mac_address_string (char*,char*,void*,struct printf_spec,char const*) ; 
 char* number (char*,char*,unsigned long,struct printf_spec) ; 
 char* resource_string (char*,char*,void*,struct printf_spec,char const*) ; 
 char* string (char*,char*,char*,struct printf_spec) ; 
 char* symbol_string (char*,char*,void*,struct printf_spec,char const) ; 
 char* uuid_string (char*,char*,void*,struct printf_spec,char const*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *pointer(const char *fmt, char *buf, char *end, void *ptr,
			struct printf_spec spec)
{
	if (!ptr && *fmt != 'K')
		return string(buf, end, "(null)", spec);

	switch (*fmt) {
	case 'F':
	case 'f':
		ptr = dereference_function_descriptor(ptr);
		/* Fallthrough */
	case 'S':
	case 's':
		return symbol_string(buf, end, ptr, spec, *fmt);
	case 'R':
	case 'r':
		return resource_string(buf, end, ptr, spec, fmt);
	case 'M':			/* Colon separated: 00:01:02:03:04:05 */
	case 'm':			/* Contiguous: 000102030405 */
		return mac_address_string(buf, end, ptr, spec, fmt);
	case 'I':			/* Formatted IP supported
					 * 4:	1.2.3.4
					 * 6:	0001:0203:...:0708
					 * 6c:	1::708 or 1::1.2.3.4
					 */
	case 'i':			/* Contiguous:
					 * 4:	001.002.003.004
					 * 6:   000102...0f
					 */
		switch (fmt[1]) {
		case '6':
			return ip6_addr_string(buf, end, ptr, spec, fmt);
		case '4':
			return ip4_addr_string(buf, end, ptr, spec, fmt);
		}
		break;
	case 'K':
		/*
		 * %pK cannot be used in IRQ context because its test
		 * for CAP_SYS_ADMIN would be meaningless.
		 */
		if (in_irq() || in_softirq() || in_nmi()) {
			if (spec.field_width == -1)
				spec.field_width = 2 * sizeof(void *);
			return string(buf, end, "pK-error", spec);
		} else if ((kptr_restrict == 0) ||
			 (kptr_restrict == 1 &&
			  has_capability_noaudit(current, CAP_SYS_ADMIN)))
			break;

		if (spec.field_width == -1) {
			spec.field_width = 2 * sizeof(void *);
			spec.flags |= ZEROPAD;
		}
		return number(buf, end, 0, spec);
	case 'U':
		return uuid_string(buf, end, ptr, spec, fmt);
	case 'V':
		return buf + vsnprintf(buf, end - buf,
				       ((struct va_format *)ptr)->fmt,
				       *(((struct va_format *)ptr)->va));
	}
	spec.flags |= SMALL;
	if (spec.field_width == -1) {
		spec.field_width = 2*sizeof(void *);
		spec.flags |= ZEROPAD;
	}
	spec.base = 16;

	return number(buf, end, (unsigned long) ptr, spec);
}