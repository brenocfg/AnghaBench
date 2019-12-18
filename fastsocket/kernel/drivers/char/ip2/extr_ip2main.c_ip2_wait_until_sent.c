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
typedef  int /*<<< orphan*/  i2ChanStrPtr ;
struct TYPE_4__ {int /*<<< orphan*/  driver_data; } ;
typedef  TYPE_1__* PTTY ;

/* Variables and functions */
 int /*<<< orphan*/  i2DrainOutput (int /*<<< orphan*/ ,int) ; 
 int jiffies ; 
 int /*<<< orphan*/  tty_wait_until_sent (TYPE_1__*,int) ; 

__attribute__((used)) static void
ip2_wait_until_sent ( PTTY tty, int timeout )
{
	int i = jiffies;
	i2ChanStrPtr  pCh = tty->driver_data;

	tty_wait_until_sent(tty, timeout );
	if ( (i = timeout - (jiffies -i)) > 0)
		i2DrainOutput( pCh, i );
}