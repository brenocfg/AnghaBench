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
typedef  int u_char ;
struct IsdnCardState {int debug; int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISAR_CTRL_H ; 
 int /*<<< orphan*/  ISAR_CTRL_L ; 
 int /*<<< orphan*/  ISAR_HIS ; 
 int /*<<< orphan*/  ISAR_MBOX ; 
 int /*<<< orphan*/  ISAR_WADR ; 
 int L1_DEB_HSCX ; 
 int L1_DEB_HSCX_FIFO ; 
 int /*<<< orphan*/  QuickHex (char*,int*,int) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  waitforHIA (struct IsdnCardState*,int) ; 

__attribute__((used)) static int
sendmsg(struct IsdnCardState *cs, u_char his, u_char creg, u_char len,
	u_char *msg)
{
	int i;
	
	if (!waitforHIA(cs, 4000))
		return(0);
#if DUMP_MBOXFRAME
	if (cs->debug & L1_DEB_HSCX)
		debugl1(cs, "sendmsg(%02x,%02x,%d)", his, creg, len);
#endif
	cs->BC_Write_Reg(cs, 0, ISAR_CTRL_H, creg);
	cs->BC_Write_Reg(cs, 0, ISAR_CTRL_L, len);
	cs->BC_Write_Reg(cs, 0, ISAR_WADR, 0);
	if (msg && len) {
		cs->BC_Write_Reg(cs, 1, ISAR_MBOX, msg[0]);
		for (i=1; i<len; i++)
			cs->BC_Write_Reg(cs, 2, ISAR_MBOX, msg[i]);
#if DUMP_MBOXFRAME>1
		if (cs->debug & L1_DEB_HSCX_FIFO) {
			char tmp[256], *t;
			
			i = len;
			while (i>0) {
				t = tmp;
				t += sprintf(t, "sendmbox cnt %d", len);
				QuickHex(t, &msg[len-i], (i>64) ? 64:i);
				debugl1(cs, tmp);
				i -= 64;
			}
		}
#endif
	}
	cs->BC_Write_Reg(cs, 1, ISAR_HIS, his);
	waitforHIA(cs, 10000);
	return(1);
}