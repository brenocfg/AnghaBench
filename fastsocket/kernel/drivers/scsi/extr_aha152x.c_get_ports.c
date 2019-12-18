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
 int ENATNTARG ; 
 int ENAUTOATNI ; 
 int ENAUTOATNO ; 
 int ENAUTOATNP ; 
 int ENBUSFREE ; 
 int ENDMA ; 
 int ENDMADONE ; 
 int ENPHASECHG ; 
 int ENPHASEMIS ; 
 int ENREQINIT ; 
 int ENRESELI ; 
 int ENSCSIPERR ; 
 int ENSDONE ; 
 int ENSELDI ; 
 int ENSELDO ; 
 int ENSELI ; 
 int ENSELINGO ; 
 int ENSELO ; 
 int ENSELTIMO ; 
 int ENSPIORDY ; 
 int ENSWRAP ; 
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
 int /*<<< orphan*/  SPRINTF (char*,...) ; 
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
 TYPE_1__* states ; 

__attribute__((used)) static int get_ports(struct Scsi_Host *shpnt, char *pos)
{
	char *start = pos;
	int s;

	SPRINTF("\n%s: %s(%s) ", CURRENT_SC ? "on bus" : "waiting", states[STATE].name, states[PREVSTATE].name);

	s = GETPORT(SCSISEQ);
	SPRINTF("SCSISEQ( ");
	if (s & TEMODEO)
		SPRINTF("TARGET MODE ");
	if (s & ENSELO)
		SPRINTF("SELO ");
	if (s & ENSELI)
		SPRINTF("SELI ");
	if (s & ENRESELI)
		SPRINTF("RESELI ");
	if (s & ENAUTOATNO)
		SPRINTF("AUTOATNO ");
	if (s & ENAUTOATNI)
		SPRINTF("AUTOATNI ");
	if (s & ENAUTOATNP)
		SPRINTF("AUTOATNP ");
	if (s & SCSIRSTO)
		SPRINTF("SCSIRSTO ");
	SPRINTF(");");

	SPRINTF(" SCSISIG(");
	s = GETPORT(SCSISIG);
	switch (s & P_MASK) {
	case P_DATAO:
		SPRINTF("DATA OUT");
		break;
	case P_DATAI:
		SPRINTF("DATA IN");
		break;
	case P_CMD:
		SPRINTF("COMMAND");
		break;
	case P_STATUS:
		SPRINTF("STATUS");
		break;
	case P_MSGO:
		SPRINTF("MESSAGE OUT");
		break;
	case P_MSGI:
		SPRINTF("MESSAGE IN");
		break;
	default:
		SPRINTF("*invalid*");
		break;
	}

	SPRINTF("); ");

	SPRINTF("INTSTAT (%s); ", TESTHI(DMASTAT, INTSTAT) ? "hi" : "lo");

	SPRINTF("SSTAT( ");
	s = GETPORT(SSTAT0);
	if (s & TARGET)
		SPRINTF("TARGET ");
	if (s & SELDO)
		SPRINTF("SELDO ");
	if (s & SELDI)
		SPRINTF("SELDI ");
	if (s & SELINGO)
		SPRINTF("SELINGO ");
	if (s & SWRAP)
		SPRINTF("SWRAP ");
	if (s & SDONE)
		SPRINTF("SDONE ");
	if (s & SPIORDY)
		SPRINTF("SPIORDY ");
	if (s & DMADONE)
		SPRINTF("DMADONE ");

	s = GETPORT(SSTAT1);
	if (s & SELTO)
		SPRINTF("SELTO ");
	if (s & ATNTARG)
		SPRINTF("ATNTARG ");
	if (s & SCSIRSTI)
		SPRINTF("SCSIRSTI ");
	if (s & PHASEMIS)
		SPRINTF("PHASEMIS ");
	if (s & BUSFREE)
		SPRINTF("BUSFREE ");
	if (s & SCSIPERR)
		SPRINTF("SCSIPERR ");
	if (s & PHASECHG)
		SPRINTF("PHASECHG ");
	if (s & REQINIT)
		SPRINTF("REQINIT ");
	SPRINTF("); ");


	SPRINTF("SSTAT( ");

	s = GETPORT(SSTAT0) & GETPORT(SIMODE0);

	if (s & TARGET)
		SPRINTF("TARGET ");
	if (s & SELDO)
		SPRINTF("SELDO ");
	if (s & SELDI)
		SPRINTF("SELDI ");
	if (s & SELINGO)
		SPRINTF("SELINGO ");
	if (s & SWRAP)
		SPRINTF("SWRAP ");
	if (s & SDONE)
		SPRINTF("SDONE ");
	if (s & SPIORDY)
		SPRINTF("SPIORDY ");
	if (s & DMADONE)
		SPRINTF("DMADONE ");

	s = GETPORT(SSTAT1) & GETPORT(SIMODE1);

	if (s & SELTO)
		SPRINTF("SELTO ");
	if (s & ATNTARG)
		SPRINTF("ATNTARG ");
	if (s & SCSIRSTI)
		SPRINTF("SCSIRSTI ");
	if (s & PHASEMIS)
		SPRINTF("PHASEMIS ");
	if (s & BUSFREE)
		SPRINTF("BUSFREE ");
	if (s & SCSIPERR)
		SPRINTF("SCSIPERR ");
	if (s & PHASECHG)
		SPRINTF("PHASECHG ");
	if (s & REQINIT)
		SPRINTF("REQINIT ");
	SPRINTF("); ");

	SPRINTF("SXFRCTL0( ");

	s = GETPORT(SXFRCTL0);
	if (s & SCSIEN)
		SPRINTF("SCSIEN ");
	if (s & DMAEN)
		SPRINTF("DMAEN ");
	if (s & CH1)
		SPRINTF("CH1 ");
	if (s & CLRSTCNT)
		SPRINTF("CLRSTCNT ");
	if (s & SPIOEN)
		SPRINTF("SPIOEN ");
	if (s & CLRCH1)
		SPRINTF("CLRCH1 ");
	SPRINTF("); ");

	SPRINTF("SIGNAL( ");

	s = GETPORT(SCSISIG);
	if (s & SIG_ATNI)
		SPRINTF("ATNI ");
	if (s & SIG_SELI)
		SPRINTF("SELI ");
	if (s & SIG_BSYI)
		SPRINTF("BSYI ");
	if (s & SIG_REQI)
		SPRINTF("REQI ");
	if (s & SIG_ACKI)
		SPRINTF("ACKI ");
	SPRINTF("); ");

	SPRINTF("SELID(%02x), ", GETPORT(SELID));

	SPRINTF("STCNT(%d), ", GETSTCNT());

	SPRINTF("SSTAT2( ");

	s = GETPORT(SSTAT2);
	if (s & SOFFSET)
		SPRINTF("SOFFSET ");
	if (s & SEMPTY)
		SPRINTF("SEMPTY ");
	if (s & SFULL)
		SPRINTF("SFULL ");
	SPRINTF("); SFCNT (%d); ", s & (SFULL | SFCNT));

	s = GETPORT(SSTAT3);
	SPRINTF("SCSICNT (%d), OFFCNT(%d), ", (s & 0xf0) >> 4, s & 0x0f);

	SPRINTF("SSTAT4( ");
	s = GETPORT(SSTAT4);
	if (s & SYNCERR)
		SPRINTF("SYNCERR ");
	if (s & FWERR)
		SPRINTF("FWERR ");
	if (s & FRERR)
		SPRINTF("FRERR ");
	SPRINTF("); ");

	SPRINTF("DMACNTRL0( ");
	s = GETPORT(DMACNTRL0);
	SPRINTF("%s ", s & _8BIT ? "8BIT" : "16BIT");
	SPRINTF("%s ", s & DMA ? "DMA" : "PIO");
	SPRINTF("%s ", s & WRITE_READ ? "WRITE" : "READ");
	if (s & ENDMA)
		SPRINTF("ENDMA ");
	if (s & INTEN)
		SPRINTF("INTEN ");
	if (s & RSTFIFO)
		SPRINTF("RSTFIFO ");
	if (s & SWINT)
		SPRINTF("SWINT ");
	SPRINTF("); ");

	SPRINTF("DMASTAT( ");
	s = GETPORT(DMASTAT);
	if (s & ATDONE)
		SPRINTF("ATDONE ");
	if (s & WORDRDY)
		SPRINTF("WORDRDY ");
	if (s & DFIFOFULL)
		SPRINTF("DFIFOFULL ");
	if (s & DFIFOEMP)
		SPRINTF("DFIFOEMP ");
	SPRINTF(")\n");

	SPRINTF("enabled interrupts( ");

	s = GETPORT(SIMODE0);
	if (s & ENSELDO)
		SPRINTF("ENSELDO ");
	if (s & ENSELDI)
		SPRINTF("ENSELDI ");
	if (s & ENSELINGO)
		SPRINTF("ENSELINGO ");
	if (s & ENSWRAP)
		SPRINTF("ENSWRAP ");
	if (s & ENSDONE)
		SPRINTF("ENSDONE ");
	if (s & ENSPIORDY)
		SPRINTF("ENSPIORDY ");
	if (s & ENDMADONE)
		SPRINTF("ENDMADONE ");

	s = GETPORT(SIMODE1);
	if (s & ENSELTIMO)
		SPRINTF("ENSELTIMO ");
	if (s & ENATNTARG)
		SPRINTF("ENATNTARG ");
	if (s & ENPHASEMIS)
		SPRINTF("ENPHASEMIS ");
	if (s & ENBUSFREE)
		SPRINTF("ENBUSFREE ");
	if (s & ENSCSIPERR)
		SPRINTF("ENSCSIPERR ");
	if (s & ENPHASECHG)
		SPRINTF("ENPHASECHG ");
	if (s & ENREQINIT)
		SPRINTF("ENREQINIT ");
	SPRINTF(")\n");

	return (pos - start);
}