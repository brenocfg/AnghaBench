#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fmt; int pfch; int ssic; int c64; scalar_t__ cpa; scalar_t__ key; scalar_t__ i2k; scalar_t__ lpm; scalar_t__ spnd; scalar_t__ intparm; } ;
union orb {TYPE_2__ cmd; } ;
typedef  scalar_t__ u32 ;
struct TYPE_9__ {int /*<<< orphan*/  actl; } ;
struct TYPE_10__ {TYPE_3__ cmd; } ;
struct TYPE_11__ {TYPE_4__ scsw; } ;
struct TYPE_7__ {scalar_t__ prefetch; scalar_t__ inter; scalar_t__ suspend; } ;
struct subchannel {scalar_t__ lpm; TYPE_5__ schib; int /*<<< orphan*/  schid; TYPE_1__ options; int /*<<< orphan*/  dev; } ;
struct ccw1 {int dummy; } ;
typedef  int /*<<< orphan*/  ccode ;
typedef  scalar_t__ addr_t ;
typedef  scalar_t__ __u8 ;
typedef  scalar_t__ __u32 ;
struct TYPE_12__ {union orb orb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_HEX_EVENT (int,int*,int) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  SCSW_ACTL_START_PEND ; 
 scalar_t__ __pa (struct ccw1*) ; 
 int cio_start_handle_notoper (struct subchannel*,scalar_t__) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (union orb*,int /*<<< orphan*/ ,int) ; 
 int ssch (int /*<<< orphan*/ ,union orb*) ; 
 TYPE_6__* to_io_private (struct subchannel*) ; 

int
cio_start_key (struct subchannel *sch,	/* subchannel structure */
	       struct ccw1 * cpa,	/* logical channel prog addr */
	       __u8 lpm,		/* logical path mask */
	       __u8 key)                /* storage key */
{
	int ccode;
	union orb *orb;

	CIO_TRACE_EVENT(5, "stIO");
	CIO_TRACE_EVENT(5, dev_name(&sch->dev));

	orb = &to_io_private(sch)->orb;
	memset(orb, 0, sizeof(union orb));
	/* sch is always under 2G. */
	orb->cmd.intparm = (u32)(addr_t)sch;
	orb->cmd.fmt = 1;

	orb->cmd.pfch = sch->options.prefetch == 0;
	orb->cmd.spnd = sch->options.suspend;
	orb->cmd.ssic = sch->options.suspend && sch->options.inter;
	orb->cmd.lpm = (lpm != 0) ? lpm : sch->lpm;
#ifdef CONFIG_64BIT
	/*
	 * for 64 bit we always support 64 bit IDAWs with 4k page size only
	 */
	orb->cmd.c64 = 1;
	orb->cmd.i2k = 0;
#endif
	orb->cmd.key = key >> 4;
	/* issue "Start Subchannel" */
	orb->cmd.cpa = (__u32) __pa(cpa);
	ccode = ssch(sch->schid, orb);

	/* process condition code */
	CIO_HEX_EVENT(5, &ccode, sizeof(ccode));

	switch (ccode) {
	case 0:
		/*
		 * initialize device status information
		 */
		sch->schib.scsw.cmd.actl |= SCSW_ACTL_START_PEND;
		return 0;
	case 1:		/* status pending */
	case 2:		/* busy */
		return -EBUSY;
	case 3:		/* device/path not operational */
		return cio_start_handle_notoper(sch, lpm);
	default:
		return ccode;
	}
}