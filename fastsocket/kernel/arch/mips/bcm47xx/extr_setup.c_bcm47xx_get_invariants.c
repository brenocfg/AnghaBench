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
typedef  void* u16 ;
struct ssb_sprom {int dummy; } ;
struct TYPE_2__ {int revision; void* et1mdcport; void* et0mdcport; void* et1phyaddr; void* et0phyaddr; int /*<<< orphan*/  et1mac; int /*<<< orphan*/  et0mac; void* rev; void* type; } ;
struct ssb_init_invariants {TYPE_1__ sprom; TYPE_1__ boardinfo; } ;
struct ssb_bus {int dummy; } ;
struct ssb_boardinfo {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ cfe_getenv (char*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* simple_strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  str2eaddr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm47xx_get_invariants(struct ssb_bus *bus,
				   struct ssb_init_invariants *iv)
{
	char buf[100];

	/* Fill boardinfo structure */
	memset(&(iv->boardinfo), 0 , sizeof(struct ssb_boardinfo));

	if (cfe_getenv("boardvendor", buf, sizeof(buf)) >= 0)
		iv->boardinfo.type = (u16)simple_strtoul(buf, NULL, 0);
	if (cfe_getenv("boardtype", buf, sizeof(buf)) >= 0)
		iv->boardinfo.type = (u16)simple_strtoul(buf, NULL, 0);
	if (cfe_getenv("boardrev", buf, sizeof(buf)) >= 0)
		iv->boardinfo.rev = (u16)simple_strtoul(buf, NULL, 0);

	/* Fill sprom structure */
	memset(&(iv->sprom), 0, sizeof(struct ssb_sprom));
	iv->sprom.revision = 3;

	if (cfe_getenv("et0macaddr", buf, sizeof(buf)) >= 0)
		str2eaddr(buf, iv->sprom.et0mac);
	if (cfe_getenv("et1macaddr", buf, sizeof(buf)) >= 0)
		str2eaddr(buf, iv->sprom.et1mac);
	if (cfe_getenv("et0phyaddr", buf, sizeof(buf)) >= 0)
		iv->sprom.et0phyaddr = simple_strtoul(buf, NULL, 10);
	if (cfe_getenv("et1phyaddr", buf, sizeof(buf)) >= 0)
		iv->sprom.et1phyaddr = simple_strtoul(buf, NULL, 10);
	if (cfe_getenv("et0mdcport", buf, sizeof(buf)) >= 0)
		iv->sprom.et0mdcport = simple_strtoul(buf, NULL, 10);
	if (cfe_getenv("et1mdcport", buf, sizeof(buf)) >= 0)
		iv->sprom.et1mdcport = simple_strtoul(buf, NULL, 10);

	return 0;
}