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
struct TYPE_2__ {int interface_type; } ;
struct sh_mobile_lcdc_chan {int ldmt1r_value; TYPE_1__ cfg; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RGB12A 145 
#define  RGB12B 144 
#define  RGB16 143 
#define  RGB18 142 
#define  RGB24 141 
#define  RGB8 140 
#define  RGB9 139 
#define  SYS12 138 
#define  SYS16A 137 
#define  SYS16B 136 
#define  SYS16C 135 
#define  SYS18 134 
#define  SYS24 133 
#define  SYS8A 132 
#define  SYS8B 131 
#define  SYS8C 130 
#define  SYS8D 129 
#define  SYS9 128 
 scalar_t__ lcdc_chan_is_sublcd (struct sh_mobile_lcdc_chan*) ; 

__attribute__((used)) static int sh_mobile_lcdc_check_interface(struct sh_mobile_lcdc_chan *ch)
{
	int ifm, miftyp;

	switch (ch->cfg.interface_type) {
	case RGB8: ifm = 0; miftyp = 0; break;
	case RGB9: ifm = 0; miftyp = 4; break;
	case RGB12A: ifm = 0; miftyp = 5; break;
	case RGB12B: ifm = 0; miftyp = 6; break;
	case RGB16: ifm = 0; miftyp = 7; break;
	case RGB18: ifm = 0; miftyp = 10; break;
	case RGB24: ifm = 0; miftyp = 11; break;
	case SYS8A: ifm = 1; miftyp = 0; break;
	case SYS8B: ifm = 1; miftyp = 1; break;
	case SYS8C: ifm = 1; miftyp = 2; break;
	case SYS8D: ifm = 1; miftyp = 3; break;
	case SYS9: ifm = 1; miftyp = 4; break;
	case SYS12: ifm = 1; miftyp = 5; break;
	case SYS16A: ifm = 1; miftyp = 7; break;
	case SYS16B: ifm = 1; miftyp = 8; break;
	case SYS16C: ifm = 1; miftyp = 9; break;
	case SYS18: ifm = 1; miftyp = 10; break;
	case SYS24: ifm = 1; miftyp = 11; break;
	default: goto bad;
	}

	/* SUBLCD only supports SYS interface */
	if (lcdc_chan_is_sublcd(ch)) {
		if (ifm == 0)
			goto bad;
		else
			ifm = 0;
	}

	ch->ldmt1r_value = (ifm << 12) | miftyp;
	return 0;
 bad:
	return -EINVAL;
}