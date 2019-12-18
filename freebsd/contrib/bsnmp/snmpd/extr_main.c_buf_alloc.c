#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rxbuf; int /*<<< orphan*/  txbuf; } ;
struct TYPE_3__ {int /*<<< orphan*/  noRxbuf; int /*<<< orphan*/  noTxbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_CRIT ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 TYPE_2__ snmpd ; 
 TYPE_1__ snmpd_stats ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

void *
buf_alloc(int tx)
{
	void *buf;

	if ((buf = malloc(tx ? snmpd.txbuf : snmpd.rxbuf)) == NULL) {
		syslog(LOG_CRIT, "cannot allocate buffer");
		if (tx)
			snmpd_stats.noTxbuf++;
		else
			snmpd_stats.noRxbuf++;
		return (NULL);
	}
	return (buf);
}