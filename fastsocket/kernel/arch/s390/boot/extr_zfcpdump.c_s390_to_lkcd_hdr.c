#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct dump_hdr_s390 {int tod; scalar_t__ arch_id; scalar_t__ cpu_id; int /*<<< orphan*/  dump_level; int /*<<< orphan*/  page_size; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  memory_end; int /*<<< orphan*/  memory_start; int /*<<< orphan*/  memory_size; } ;
struct TYPE_2__ {int tv_sec; int tv_usec; } ;
struct dump_hdr_lkcd {int header_size; TYPE_1__ time; int /*<<< orphan*/  version; int /*<<< orphan*/  magic_number; int /*<<< orphan*/  utsname_domainname; int /*<<< orphan*/  utsname_version; int /*<<< orphan*/  utsname_release; int /*<<< orphan*/  utsname_nodename; int /*<<< orphan*/  utsname_sysname; int /*<<< orphan*/  utsname_machine; int /*<<< orphan*/  panic_string; int /*<<< orphan*/  dump_level; int /*<<< orphan*/  page_size; int /*<<< orphan*/  num_dump_pages; int /*<<< orphan*/  memory_end; int /*<<< orphan*/  memory_start; int /*<<< orphan*/  memory_size; } ;
typedef  int __u64 ;

/* Variables and functions */
 scalar_t__ DH_ARCH_ID_S390 ; 
 scalar_t__ DH_ARCH_ID_S390X ; 
 int /*<<< orphan*/  DUMP_MAGIC_NUMBER ; 
 int /*<<< orphan*/  DUMP_VERSION_NUMBER ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void s390_to_lkcd_hdr(struct dump_hdr_s390 *s390_dh,
			     struct dump_hdr_lkcd *dh)
{
	struct timeval h_time;

	/* adjust todclock to 1970 */
	__u64 tod = s390_dh->tod;
	tod -= 0x8126d60e46000000LL - (0x3c26700LL * 1000000 * 4096);
	tod >>= 12;
	h_time.tv_sec  = tod / 1000000;
	h_time.tv_usec = tod % 1000000;

	dh->memory_size    = s390_dh->memory_size;
	dh->memory_start   = s390_dh->memory_start;
	dh->memory_end     = s390_dh->memory_end;
	dh->num_dump_pages = s390_dh->num_pages;
	dh->page_size      = s390_dh->page_size;
	dh->dump_level     = s390_dh->dump_level;

	sprintf(dh->panic_string, "zSeries-dump (CPUID = %16llx)",
		(unsigned long long) s390_dh->cpu_id);

	if (s390_dh->arch_id == DH_ARCH_ID_S390)
		strcpy(dh->utsname_machine, "s390");
	else if (s390_dh->arch_id == DH_ARCH_ID_S390X)
		strcpy(dh->utsname_machine, "s390x");
	else
		strcpy(dh->utsname_machine, "<unknown>");

	strcpy(dh->utsname_sysname, "<unknown>");
	strcpy(dh->utsname_nodename, "<unknown>");
	strcpy(dh->utsname_release, "<unknown>");
	strcpy(dh->utsname_version, "<unknown>");
	strcpy(dh->utsname_domainname, "<unknown>");

	dh->magic_number   = DUMP_MAGIC_NUMBER;
	dh->version        = DUMP_VERSION_NUMBER;
	dh->header_size    = sizeof(struct dump_hdr_lkcd);
	dh->time.tv_sec    = h_time.tv_sec;
	dh->time.tv_usec   = h_time.tv_usec;
}