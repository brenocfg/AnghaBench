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
struct vpd_prom {int dummy; } ;
struct Host {scalar_t__ Caddr; } ;

/* Variables and functions */
 int RIO_DEBUG_PROBE ; 
 scalar_t__ RIO_VPD_ROM ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  my_hd (char*,int) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int rio_debug ; 
 int /*<<< orphan*/  rio_dprintk (int,char*,scalar_t__) ; 

__attribute__((used)) static struct vpd_prom *get_VPD_PROM(struct Host *hp)
{
	static struct vpd_prom vpdp;
	char *p;
	int i;

	func_enter();
	rio_dprintk(RIO_DEBUG_PROBE, "Going to verify vpd prom at %p.\n", hp->Caddr + RIO_VPD_ROM);

	p = (char *) &vpdp;
	for (i = 0; i < sizeof(struct vpd_prom); i++)
		*p++ = readb(hp->Caddr + RIO_VPD_ROM + i * 2);
	/* read_rio_byte (hp, RIO_VPD_ROM + i*2); */

	/* Terminate the identifier string.
	 *** requires one extra byte in struct vpd_prom *** */
	*p++ = 0;

	if (rio_debug & RIO_DEBUG_PROBE)
		my_hd((char *) &vpdp, 0x20);

	func_exit();

	return &vpdp;
}