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
typedef  int u32 ;
typedef  int u16 ;
struct cmdstring {int channelnr; int prestringlen; int poststringlen; int /*<<< orphan*/  postcmd; int /*<<< orphan*/  precmd; } ;
typedef  int /*<<< orphan*/  cmds ;

/* Variables and functions */
 int DUM_COM_BASE ; 
 int EINVAL ; 
 int EIOREMAPFAILED ; 
 int MAX_DUM_CHANNELS ; 
 int ioread32 (int*) ; 
 scalar_t__ ioremap_nocache (int,int) ; 
 int /*<<< orphan*/  iounmap (int*) ; 
 int /*<<< orphan*/  iowrite16 (int,int*) ; 

__attribute__((used)) static int put_cmd_string(struct cmdstring cmds)
{
	u16 *cmd_str_virtaddr;
	u32 *cmd_ptr0_virtaddr;
	u32 cmd_str_physaddr;

	int i = cmds.channelnr;

	if (i < 0 || i > MAX_DUM_CHANNELS)
		return -EINVAL;
	else if ((cmd_ptr0_virtaddr =
		  (int *)ioremap_nocache(DUM_COM_BASE,
					 sizeof(int) * MAX_DUM_CHANNELS)) ==
		 NULL)
		return -EIOREMAPFAILED;
	else {
		cmd_str_physaddr = ioread32(&cmd_ptr0_virtaddr[cmds.channelnr]);
		if ((cmd_str_virtaddr =
		     (u16 *) ioremap_nocache(cmd_str_physaddr,
					     sizeof(cmds))) == NULL) {
			iounmap(cmd_ptr0_virtaddr);
			return -EIOREMAPFAILED;
		} else {
			int t;
			for (t = 0; t < 8; t++)
				iowrite16(*((u16 *)&cmds.prestringlen + t),
					  cmd_str_virtaddr + t);

			for (t = 0; t < cmds.prestringlen / 2; t++)
				 iowrite16(*((u16 *)&cmds.precmd + t),
					   cmd_str_virtaddr + t + 8);

			for (t = 0; t < cmds.poststringlen / 2; t++)
				iowrite16(*((u16 *)&cmds.postcmd + t),
					  cmd_str_virtaddr + t + 8 +
					  	cmds.prestringlen / 2);

			iounmap(cmd_ptr0_virtaddr);
			iounmap(cmd_str_virtaddr);
		}
	}

	return 0;
}