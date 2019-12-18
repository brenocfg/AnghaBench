#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tPofFileHdr ;
struct TYPE_7__ {unsigned char* BootBuf; } ;
struct boot_data {int last_error; TYPE_1__ buf; int /*<<< orphan*/  pof_state; scalar_t__ BufSize; } ;
struct TYPE_8__ {int debug_flags; int /*<<< orphan*/  state; scalar_t__ (* testram ) (TYPE_2__*) ;int /*<<< orphan*/  (* stopcard ) (TYPE_2__*) ;struct boot_data* boot; } ;
typedef  TYPE_2__ hysdn_card ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_STATE_BOOTERR ; 
 int /*<<< orphan*/  CARD_STATE_BOOTING ; 
 int EFAULT ; 
 int ERR_ALREADY_BOOT ; 
 int ERR_BOARD_DPRAM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LOG_MEM_ERR ; 
 int LOG_POF_OPEN ; 
 int /*<<< orphan*/  POF_READ_FILE_HEAD ; 
 int /*<<< orphan*/  StartDecryption (struct boot_data*) ; 
 int /*<<< orphan*/  hysdn_addlog (TYPE_2__*,char*) ; 
 struct boot_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ stub2 (TYPE_2__*) ; 

int
pof_write_open(hysdn_card * card, unsigned char **bufp)
{
	struct boot_data *boot;	/* pointer to boot specific data */

	if (card->boot) {
		if (card->debug_flags & LOG_POF_OPEN)
			hysdn_addlog(card, "POF open: already opened for boot");
		return (-ERR_ALREADY_BOOT);	/* boot already active */
	}
	/* error no mem available */
	if (!(boot = kzalloc(sizeof(struct boot_data), GFP_KERNEL))) {
		if (card->debug_flags & LOG_MEM_ERR)
			hysdn_addlog(card, "POF open: unable to allocate mem");
		return (-EFAULT);
	}
	card->boot = boot;
	card->state = CARD_STATE_BOOTING;

	card->stopcard(card);	/* first stop the card */
	if (card->testram(card)) {
		if (card->debug_flags & LOG_POF_OPEN)
			hysdn_addlog(card, "POF open: DPRAM test failure");
		boot->last_error = -ERR_BOARD_DPRAM;
		card->state = CARD_STATE_BOOTERR;	/* show boot error */
		return (boot->last_error);
	}
	boot->BufSize = 0;	/* Buffer is empty */
	boot->pof_state = POF_READ_FILE_HEAD;	/* read file header */
	StartDecryption(boot);	/* if POF File should be encrypted */

	if (card->debug_flags & LOG_POF_OPEN)
		hysdn_addlog(card, "POF open: success");

	*bufp = boot->buf.BootBuf;	/* point to buffer */
	return (sizeof(tPofFileHdr));
}