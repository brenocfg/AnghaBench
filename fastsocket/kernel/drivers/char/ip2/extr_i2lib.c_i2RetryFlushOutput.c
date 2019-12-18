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
typedef  TYPE_1__* i2ChanStrPtr ;
struct TYPE_4__ {int flush_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANN ; 
 int /*<<< orphan*/  CMD_STARTFL ; 
 int /*<<< orphan*/  CMD_STOPFL ; 
 int /*<<< orphan*/  ITRC_FLUSH ; 
 int /*<<< orphan*/  PTYPE_BYPASS ; 
 int /*<<< orphan*/  PTYPE_INLINE ; 
 int STARTFL_FLAG ; 
 int STOPFL_FLAG ; 
 int i2QueueCommands (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int 
i2RetryFlushOutput(i2ChanStrPtr pCh)
{
	int old_flags = pCh->flush_flags;

	ip2trace (CHANN, ITRC_FLUSH, 14, 1, old_flags );

	pCh->flush_flags = 0;	// Clear flag so we can avoid recursion
									// and queue the commands

	if ( old_flags & STARTFL_FLAG ) {
		if ( 1 == i2QueueCommands(PTYPE_BYPASS, pCh, 0, 1, CMD_STARTFL) ) {
			old_flags = STOPFL_FLAG;	//Success - send stop flush
		} else {
			old_flags = STARTFL_FLAG;	//Failure - Flag for retry later
		}

		ip2trace (CHANN, ITRC_FLUSH, 15, 1, old_flags );

	}
	if ( old_flags & STOPFL_FLAG ) {
		if (1 == i2QueueCommands(PTYPE_INLINE, pCh, 0, 1, CMD_STOPFL)) {
			old_flags = 0;	// Success - clear flags
		}

		ip2trace (CHANN, ITRC_FLUSH, 16, 1, old_flags );
	}
	pCh->flush_flags = old_flags;

	ip2trace (CHANN, ITRC_FLUSH, 17, 1, old_flags );

	return old_flags;
}