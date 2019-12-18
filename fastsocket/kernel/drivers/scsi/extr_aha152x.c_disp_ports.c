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
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ATDONE ; 
 int ATNTARG ; 
 int BUSFREE ; 
 int CH1 ; 
 int CLRCH1 ; 
 int CLRSTCNT ; 
 scalar_t__ CURRENT_SC ; 
 int DFIFOEMP ; 
 int DFIFOFULL ; 
 int DMA ; 
 int /*<<< orphan*/  DMACNTRL0 ; 
 int DMADONE ; 
 int DMAEN ; 
 int /*<<< orphan*/  DMASTAT ; 
 int ENAUTOATNI ; 
 int ENAUTOATNO ; 
 int ENAUTOATNP ; 
 int ENDMA ; 
 int ENRESELI ; 
 int ENSELI ; 
 int ENSELO ; 
 int FRERR ; 
 int FWERR ; 
 int GETPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GETSTCNT () ; 
 int INTEN ; 
 int /*<<< orphan*/  INTSTAT ; 
 int PHASECHG ; 
 int PHASEMIS ; 
 size_t PREVSTATE ; 
#define  P_CMD 133 
#define  P_DATAI 132 
#define  P_DATAO 131 
 int P_MASK ; 
#define  P_MSGI 130 
#define  P_MSGO 129 
#define  P_STATUS 128 
 int REQINIT ; 
 int RSTFIFO ; 
 int SCSIEN ; 
 int SCSIPERR ; 
 int SCSIRSTI ; 
 int SCSIRSTO ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int /*<<< orphan*/  SCSISIG ; 
 int SDONE ; 
 int SELDI ; 
 int SELDO ; 
 int /*<<< orphan*/  SELID ; 
 int SELINGO ; 
 int SELTO ; 
 int SEMPTY ; 
 int SFCNT ; 
 int SFULL ; 
 int SIG_ACKI ; 
 int SIG_ATNI ; 
 int SIG_BSYI ; 
 int SIG_REQI ; 
 int SIG_SELI ; 
 int /*<<< orphan*/  SIMODE0 ; 
 int /*<<< orphan*/  SIMODE1 ; 
 int SOFFSET ; 
 int SPIOEN ; 
 int SPIORDY ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int /*<<< orphan*/  SSTAT1 ; 
 int /*<<< orphan*/  SSTAT2 ; 
 int /*<<< orphan*/  SSTAT3 ; 
 int /*<<< orphan*/  SSTAT4 ; 
 size_t STATE ; 
 int SWINT ; 
 int SWRAP ; 
 int /*<<< orphan*/  SXFRCTL0 ; 
 int SYNCERR ; 
 int TARGET ; 
 int TEMODEO ; 
 scalar_t__ TESTHI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WORDRDY ; 
 int WRITE_READ ; 
 int _8BIT ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_1__* states ; 

__attribute__((used)) static void disp_ports(struct Scsi_Host *shpnt)
{
#if defined(AHA152X_DEBUG)
	int s;

	printk("\n%s: %s(%s) ",
		CURRENT_SC ? "busy" : "waiting",
		states[STATE].name,
		states[PREVSTATE].name);

	s = GETPORT(SCSISEQ);
	printk("SCSISEQ( ");
	if (s & TEMODEO)
		printk("TARGET MODE ");
	if (s & ENSELO)
		printk("SELO ");
	if (s & ENSELI)
		printk("SELI ");
	if (s & ENRESELI)
		printk("RESELI ");
	if (s & ENAUTOATNO)
		printk("AUTOATNO ");
	if (s & ENAUTOATNI)
		printk("AUTOATNI ");
	if (s & ENAUTOATNP)
		printk("AUTOATNP ");
	if (s & SCSIRSTO)
		printk("SCSIRSTO ");
	printk(");");

	printk(" SCSISIG(");
	s = GETPORT(SCSISIG);
	switch (s & P_MASK) {
	case P_DATAO:
		printk("DATA OUT");
		break;
	case P_DATAI:
		printk("DATA IN");
		break;
	case P_CMD:
		printk("COMMAND");
		break;
	case P_STATUS:
		printk("STATUS");
		break;
	case P_MSGO:
		printk("MESSAGE OUT");
		break;
	case P_MSGI:
		printk("MESSAGE IN");
		break;
	default:
		printk("*invalid*");
		break;
	}

	printk("); ");

	printk("INTSTAT (%s); ", TESTHI(DMASTAT, INTSTAT) ? "hi" : "lo");

	printk("SSTAT( ");
	s = GETPORT(SSTAT0);
	if (s & TARGET)
		printk("TARGET ");
	if (s & SELDO)
		printk("SELDO ");
	if (s & SELDI)
		printk("SELDI ");
	if (s & SELINGO)
		printk("SELINGO ");
	if (s & SWRAP)
		printk("SWRAP ");
	if (s & SDONE)
		printk("SDONE ");
	if (s & SPIORDY)
		printk("SPIORDY ");
	if (s & DMADONE)
		printk("DMADONE ");

	s = GETPORT(SSTAT1);
	if (s & SELTO)
		printk("SELTO ");
	if (s & ATNTARG)
		printk("ATNTARG ");
	if (s & SCSIRSTI)
		printk("SCSIRSTI ");
	if (s & PHASEMIS)
		printk("PHASEMIS ");
	if (s & BUSFREE)
		printk("BUSFREE ");
	if (s & SCSIPERR)
		printk("SCSIPERR ");
	if (s & PHASECHG)
		printk("PHASECHG ");
	if (s & REQINIT)
		printk("REQINIT ");
	printk("); ");


	printk("SSTAT( ");

	s = GETPORT(SSTAT0) & GETPORT(SIMODE0);

	if (s & TARGET)
		printk("TARGET ");
	if (s & SELDO)
		printk("SELDO ");
	if (s & SELDI)
		printk("SELDI ");
	if (s & SELINGO)
		printk("SELINGO ");
	if (s & SWRAP)
		printk("SWRAP ");
	if (s & SDONE)
		printk("SDONE ");
	if (s & SPIORDY)
		printk("SPIORDY ");
	if (s & DMADONE)
		printk("DMADONE ");

	s = GETPORT(SSTAT1) & GETPORT(SIMODE1);

	if (s & SELTO)
		printk("SELTO ");
	if (s & ATNTARG)
		printk("ATNTARG ");
	if (s & SCSIRSTI)
		printk("SCSIRSTI ");
	if (s & PHASEMIS)
		printk("PHASEMIS ");
	if (s & BUSFREE)
		printk("BUSFREE ");
	if (s & SCSIPERR)
		printk("SCSIPERR ");
	if (s & PHASECHG)
		printk("PHASECHG ");
	if (s & REQINIT)
		printk("REQINIT ");
	printk("); ");

	printk("SXFRCTL0( ");

	s = GETPORT(SXFRCTL0);
	if (s & SCSIEN)
		printk("SCSIEN ");
	if (s & DMAEN)
		printk("DMAEN ");
	if (s & CH1)
		printk("CH1 ");
	if (s & CLRSTCNT)
		printk("CLRSTCNT ");
	if (s & SPIOEN)
		printk("SPIOEN ");
	if (s & CLRCH1)
		printk("CLRCH1 ");
	printk("); ");

	printk("SIGNAL( ");

	s = GETPORT(SCSISIG);
	if (s & SIG_ATNI)
		printk("ATNI ");
	if (s & SIG_SELI)
		printk("SELI ");
	if (s & SIG_BSYI)
		printk("BSYI ");
	if (s & SIG_REQI)
		printk("REQI ");
	if (s & SIG_ACKI)
		printk("ACKI ");
	printk("); ");

	printk("SELID (%02x), ", GETPORT(SELID));

	printk("STCNT (%d), ", GETSTCNT());
	
	printk("SSTAT2( ");

	s = GETPORT(SSTAT2);
	if (s & SOFFSET)
		printk("SOFFSET ");
	if (s & SEMPTY)
		printk("SEMPTY ");
	if (s & SFULL)
		printk("SFULL ");
	printk("); SFCNT (%d); ", s & (SFULL | SFCNT));

	s = GETPORT(SSTAT3);
	printk("SCSICNT (%d), OFFCNT(%d), ", (s & 0xf0) >> 4, s & 0x0f);

	printk("SSTAT4( ");
	s = GETPORT(SSTAT4);
	if (s & SYNCERR)
		printk("SYNCERR ");
	if (s & FWERR)
		printk("FWERR ");
	if (s & FRERR)
		printk("FRERR ");
	printk("); ");

	printk("DMACNTRL0( ");
	s = GETPORT(DMACNTRL0);
	printk("%s ", s & _8BIT ? "8BIT" : "16BIT");
	printk("%s ", s & DMA ? "DMA" : "PIO");
	printk("%s ", s & WRITE_READ ? "WRITE" : "READ");
	if (s & ENDMA)
		printk("ENDMA ");
	if (s & INTEN)
		printk("INTEN ");
	if (s & RSTFIFO)
		printk("RSTFIFO ");
	if (s & SWINT)
		printk("SWINT ");
	printk("); ");

	printk("DMASTAT( ");
	s = GETPORT(DMASTAT);
	if (s & ATDONE)
		printk("ATDONE ");
	if (s & WORDRDY)
		printk("WORDRDY ");
	if (s & DFIFOFULL)
		printk("DFIFOFULL ");
	if (s & DFIFOEMP)
		printk("DFIFOEMP ");
	printk(")\n");
#endif
}