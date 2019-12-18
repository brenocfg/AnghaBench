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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_pfargd_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* alloca (size_t) ; 
 int /*<<< orphan*/  bcopy (void const*,char*,size_t) ; 
 int dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*) ; 

__attribute__((used)) static int
pfprint_cstr(dtrace_hdl_t *dtp, FILE *fp, const char *format,
    const dt_pfargd_t *pfd, const void *addr, size_t size, uint64_t normal)
{
	char *s = alloca(size + 1);

	bcopy(addr, s, size);
	s[size] = '\0';
	return (dt_printf(dtp, fp, format, s));
}