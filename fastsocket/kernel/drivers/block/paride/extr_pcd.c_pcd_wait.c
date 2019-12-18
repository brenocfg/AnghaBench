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
struct pcd_unit {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IDE_ERR ; 
 int /*<<< orphan*/  PCD_DELAY ; 
 int PCD_SPIN ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,char*,int,int,int,int,int) ; 
 int read_reg (struct pcd_unit*,int) ; 
 int status_reg (struct pcd_unit*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcd_wait(struct pcd_unit *cd, int go, int stop, char *fun, char *msg)
{
	int j, r, e, s, p;

	j = 0;
	while ((((r = status_reg(cd)) & go) || (stop && (!(r & stop))))
	       && (j++ < PCD_SPIN))
		udelay(PCD_DELAY);

	if ((r & (IDE_ERR & stop)) || (j >= PCD_SPIN)) {
		s = read_reg(cd, 7);
		e = read_reg(cd, 1);
		p = read_reg(cd, 2);
		if (j >= PCD_SPIN)
			e |= 0x100;
		if (fun)
			printk("%s: %s %s: alt=0x%x stat=0x%x err=0x%x"
			       " loop=%d phase=%d\n",
			       cd->name, fun, msg, r, s, e, j, p);
		return (s << 8) + r;
	}
	return 0;
}