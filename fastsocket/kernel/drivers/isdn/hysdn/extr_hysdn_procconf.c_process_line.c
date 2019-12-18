#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct conf_writedata {unsigned char* conf_line; int channel; TYPE_1__* card; } ;
struct TYPE_3__ {int debug_flags; } ;

/* Variables and functions */
 int ERR_INV_CHAN ; 
 int LOG_CNF_DATA ; 
 int LOG_CNF_LINE ; 
 int LOG_CNF_MISC ; 
 int /*<<< orphan*/  hysdn_addlog (TYPE_1__*,char*,...) ; 
 int hysdn_tx_cfgline (TYPE_1__*,unsigned char*,int) ; 

__attribute__((used)) static int
process_line(struct conf_writedata *cnf)
{
	unsigned char *cp = cnf->conf_line;
	int i;

	if (cnf->card->debug_flags & LOG_CNF_LINE)
		hysdn_addlog(cnf->card, "conf line: %s", cp);

	if (*cp == '-') {	/* option */
		cp++;		/* point to option char */

		if (*cp++ != 'c')
			return (0);	/* option unknown or used */
		i = 0;		/* start value for channel */
		while ((*cp <= '9') && (*cp >= '0'))
			i = i * 10 + *cp++ - '0';	/* get decimal number */
		if (i > 65535) {
			if (cnf->card->debug_flags & LOG_CNF_MISC)
				hysdn_addlog(cnf->card, "conf channel invalid  %d", i);
			return (-ERR_INV_CHAN);		/* invalid channel */
		}
		cnf->channel = i & 0xFFFF;	/* set new channel number */
		return (0);	/* success */
	}			/* option */
	if (*cp == '*') {	/* line to send */
		if (cnf->card->debug_flags & LOG_CNF_DATA)
			hysdn_addlog(cnf->card, "conf chan=%d %s", cnf->channel, cp);
		return (hysdn_tx_cfgline(cnf->card, cnf->conf_line + 1,
					 cnf->channel));	/* send the line without * */
	}			/* line to send */
	return (0);
}