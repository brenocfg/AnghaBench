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
struct TYPE_3__ {int /*<<< orphan*/  load_parm; } ;
struct TYPE_4__ {TYPE_1__ ccw; } ;
struct ipl_parameter_block {TYPE_2__ ipl_info; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (int /*<<< orphan*/ ,int) ; 
 size_t EINVAL ; 
 int LOADPARM_LEN ; 
 scalar_t__ isalpha (char const) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 

__attribute__((used)) static ssize_t reipl_generic_loadparm_store(struct ipl_parameter_block *ipb,
					    const char *buf, size_t len)
{
	int i, lp_len;

	/* ignore trailing newline */
	lp_len = len;
	if ((len > 0) && (buf[len - 1] == '\n'))
		lp_len--;
	/* loadparm can have max 8 characters and must not start with a blank */
	if ((lp_len > LOADPARM_LEN) || ((lp_len > 0) && (buf[0] == ' ')))
		return -EINVAL;
	/* loadparm can only contain "a-z,A-Z,0-9,SP,." */
	for (i = 0; i < lp_len; i++) {
		if (isalpha(buf[i]) || isdigit(buf[i]) || (buf[i] == ' ') ||
		    (buf[i] == '.'))
			continue;
		return -EINVAL;
	}
	/* initialize loadparm with blanks */
	memset(ipb->ipl_info.ccw.load_parm, ' ', LOADPARM_LEN);
	/* copy and convert to ebcdic */
	memcpy(ipb->ipl_info.ccw.load_parm, buf, lp_len);
	ASCEBC(ipb->ipl_info.ccw.load_parm, LOADPARM_LEN);
	return len;
}