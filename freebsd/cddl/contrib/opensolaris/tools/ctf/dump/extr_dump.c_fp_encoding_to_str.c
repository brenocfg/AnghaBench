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
typedef  int uint_t ;
typedef  int /*<<< orphan*/  encs ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
fp_encoding_to_str(uint_t encoding)
{
	static const char *const encs[] = {
		NULL, "SINGLE", "DOUBLE", "COMPLEX", "DCOMPLEX", "LDCOMPLEX",
		"LDOUBLE", "INTERVAL", "DINTERVAL", "LDINTERVAL", "IMAGINARY",
		"DIMAGINARY", "LDIMAGINARY"
	};

	static char buf[16];

	if (encoding < 1 || encoding >= (sizeof (encs) / sizeof (char *))) {
		(void) snprintf(buf, sizeof (buf), "%u", encoding);
		return (buf);
	}

	return (encs[encoding]);
}