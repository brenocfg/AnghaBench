#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ swbuf; } ;
typedef  TYPE_1__ vwsnd_port_t ;
typedef  int /*<<< orphan*/  vwsnd_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGEV (char*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DBGPV (char*) ; 
 int /*<<< orphan*/  DBGRV () ; 
 int /*<<< orphan*/  READ_INTR_MASK ; 
 int /*<<< orphan*/  WRITE_INTR_MASK ; 
 int /*<<< orphan*/  pcm_shutdown_port (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcm_shutdown(vwsnd_dev_t *devc,
			 vwsnd_port_t *rport,
			 vwsnd_port_t *wport)
{
	DBGEV("(devc=0x%p, rport=0x%p, wport=0x%p)\n", devc, rport, wport);

	if (rport && rport->swbuf) {
		DBGPV("shutting down rport\n");
		pcm_shutdown_port(devc, rport, READ_INTR_MASK);
	}
	if (wport && wport->swbuf) {
		DBGPV("shutting down wport\n");
		pcm_shutdown_port(devc, wport, WRITE_INTR_MASK);
	}
	DBGRV();
}