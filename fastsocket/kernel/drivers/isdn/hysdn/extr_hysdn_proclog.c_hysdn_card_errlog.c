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
struct TYPE_3__ {int /*<<< orphan*/  ucText; int /*<<< orphan*/  ulErrSubtype; int /*<<< orphan*/  ulErrType; } ;
typedef  TYPE_1__ tErrLogEntry ;
typedef  int /*<<< orphan*/  hysdn_card ;

/* Variables and functions */
 int /*<<< orphan*/  ERRLOG_TEXT_SIZE ; 
 int /*<<< orphan*/  put_log_buffer (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
hysdn_card_errlog(hysdn_card * card, tErrLogEntry * logp, int maxsize)
{
	char buf[ERRLOG_TEXT_SIZE + 40];

	sprintf(buf, "LOG 0x%08lX 0x%08lX : %s\n", logp->ulErrType, logp->ulErrSubtype, logp->ucText);
	put_log_buffer(card, buf);	/* output the string */
}