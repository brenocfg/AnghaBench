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
typedef  int u8 ;
struct TYPE_2__ {int err; int fatal; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int EMSGSIZE ; 
 int EPROTO ; 
#define  ICMPV6_DEST_UNREACH 131 
#define  ICMPV6_PARAMPROB 130 
#define  ICMPV6_PKT_TOOBIG 129 
 int ICMPV6_PORT_UNREACH ; 
#define  ICMPV6_TIME_EXCEED 128 
 TYPE_1__* tab_unreach ; 

int icmpv6_err_convert(u8 type, u8 code, int *err)
{
	int fatal = 0;

	*err = EPROTO;

	switch (type) {
	case ICMPV6_DEST_UNREACH:
		fatal = 1;
		if (code <= ICMPV6_PORT_UNREACH) {
			*err  = tab_unreach[code].err;
			fatal = tab_unreach[code].fatal;
		}
		break;

	case ICMPV6_PKT_TOOBIG:
		*err = EMSGSIZE;
		break;

	case ICMPV6_PARAMPROB:
		*err = EPROTO;
		fatal = 1;
		break;

	case ICMPV6_TIME_EXCEED:
		*err = EHOSTUNREACH;
		break;
	}

	return fatal;
}