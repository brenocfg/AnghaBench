#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_7__ {char* mdmreg; char* mdmcmd; size_t mdmcmdl; } ;
struct TYPE_6__ {TYPE_2__ emu; } ;
typedef  TYPE_1__ modem_info ;
typedef  TYPE_2__ atemu ;

/* Variables and functions */
 int BIT_ECHO ; 
 size_t REG_BS ; 
 size_t REG_CR ; 
 size_t REG_ECHO ; 
 size_t REG_LF ; 
 scalar_t__ cmdchar (char) ; 
 int /*<<< orphan*/  isdn_tty_at_cout (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_tty_parse_at (TYPE_1__*) ; 
 char my_toupper (char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int
isdn_tty_edit_at(const char *p, int count, modem_info * info)
{
	atemu *m = &info->emu;
	int total = 0;
	u_char c;
	char eb[2];
	int cnt;

	for (cnt = count; cnt > 0; p++, cnt--) {
		c = *p;
		total++;
		if (c == m->mdmreg[REG_CR] || c == m->mdmreg[REG_LF]) {
			/* Separator (CR or LF) */
			m->mdmcmd[m->mdmcmdl] = 0;
			if (m->mdmreg[REG_ECHO] & BIT_ECHO) {
				eb[0] = c;
				eb[1] = 0;
				isdn_tty_at_cout(eb, info);
			}
			if ((m->mdmcmdl >= 2) && (!(strncmp(m->mdmcmd, "AT", 2))))
				isdn_tty_parse_at(info);
			m->mdmcmdl = 0;
			continue;
		}
		if (c == m->mdmreg[REG_BS] && m->mdmreg[REG_BS] < 128) {
			/* Backspace-Function */
			if ((m->mdmcmdl > 2) || (!m->mdmcmdl)) {
				if (m->mdmcmdl)
					m->mdmcmdl--;
				if (m->mdmreg[REG_ECHO] & BIT_ECHO)
					isdn_tty_at_cout("\b", info);
			}
			continue;
		}
		if (cmdchar(c)) {
			if (m->mdmreg[REG_ECHO] & BIT_ECHO) {
				eb[0] = c;
				eb[1] = 0;
				isdn_tty_at_cout(eb, info);
			}
			if (m->mdmcmdl < 255) {
				c = my_toupper(c);
				switch (m->mdmcmdl) {
					case 1:
						if (c == 'T') {
							m->mdmcmd[m->mdmcmdl] = c;
							m->mdmcmd[++m->mdmcmdl] = 0;
							break;
						} else
							m->mdmcmdl = 0;
						/* Fall through, check for 'A' */
					case 0:
						if (c == 'A') {
							m->mdmcmd[m->mdmcmdl] = c;
							m->mdmcmd[++m->mdmcmdl] = 0;
						}
						break;
					default:
						m->mdmcmd[m->mdmcmdl] = c;
						m->mdmcmd[++m->mdmcmdl] = 0;
				}
			}
		}
	}
	return total;
}