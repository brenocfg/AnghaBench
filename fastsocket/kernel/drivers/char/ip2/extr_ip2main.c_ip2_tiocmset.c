#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {size_t index; } ;
struct file {int dummy; } ;
typedef  TYPE_1__* i2ChanStrPtr ;
struct TYPE_4__ {int /*<<< orphan*/  pMyBord; int /*<<< orphan*/  dataSetOut; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DTRDN ; 
 int /*<<< orphan*/  CMD_DTRUP ; 
 int /*<<< orphan*/  CMD_RTSDN ; 
 int /*<<< orphan*/  CMD_RTSUP ; 
 TYPE_1__** DevTable ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2_DTR ; 
 int /*<<< orphan*/  I2_RTS ; 
 int /*<<< orphan*/  PTYPE_INLINE ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  i2QueueCommands (int /*<<< orphan*/ ,TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serviceOutgoingFifo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip2_tiocmset(struct tty_struct *tty, struct file *file,
			unsigned int set, unsigned int clear)
{
	i2ChanStrPtr pCh = DevTable[tty->index];

	if (pCh == NULL)
		return -ENODEV;

	if (set & TIOCM_RTS) {
		i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_RTSUP);
		pCh->dataSetOut |= I2_RTS;
	}
	if (set & TIOCM_DTR) {
		i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_DTRUP);
		pCh->dataSetOut |= I2_DTR;
	}

	if (clear & TIOCM_RTS) {
		i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_RTSDN);
		pCh->dataSetOut &= ~I2_RTS;
	}
	if (clear & TIOCM_DTR) {
		i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_DTRDN);
		pCh->dataSetOut &= ~I2_DTR;
	}
	serviceOutgoingFifo( pCh->pMyBord );
	return 0;
}