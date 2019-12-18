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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int hrtime_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_pfargd_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NANOSEC ; 
 int dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static int
pfprint_time822(dtrace_hdl_t *dtp, FILE *fp, const char *format,
    const dt_pfargd_t *pfd, const void *addr, size_t size, uint64_t normal)
{
	hrtime_t time = *((uint64_t *)addr);
	time_t sec = (time_t)(time / NANOSEC);
	struct tm tm;
	char buf[64];

	(void) localtime_r(&sec, &tm);
	(void) strftime(buf, sizeof (buf), "%a, %d %b %G %T %Z", &tm);
	return (dt_printf(dtp, fp, format, buf));
}