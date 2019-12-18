#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_5__ {int pfd_flags; } ;
typedef  TYPE_1__ dt_pfargd_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DT_PFCONV_SIGNED ; 
 int pfprint_sint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_1__ const*,void const*,size_t,int /*<<< orphan*/ ) ; 
 int pfprint_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_1__ const*,void const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfprint_dint(dtrace_hdl_t *dtp, FILE *fp, const char *format,
    const dt_pfargd_t *pfd, const void *addr, size_t size, uint64_t normal)
{
	if (pfd->pfd_flags & DT_PFCONV_SIGNED)
		return (pfprint_sint(dtp, fp, format, pfd, addr, size, normal));
	else
		return (pfprint_uint(dtp, fp, format, pfd, addr, size, normal));
}