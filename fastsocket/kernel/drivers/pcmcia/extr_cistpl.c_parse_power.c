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
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_3__ {int present; int /*<<< orphan*/  flags; scalar_t__* param; } ;
typedef  TYPE_1__ cistpl_power_t ;

/* Variables and functions */
 int /*<<< orphan*/  CISTPL_POWER_HIGHZ_OK ; 
 int /*<<< orphan*/  CISTPL_POWER_HIGHZ_REQ ; 
 scalar_t__ POWER_CVT (int) ; 
 int POWER_SCALE (int) ; 

__attribute__((used)) static u_char *parse_power(u_char *p, u_char *q,
			   cistpl_power_t *pwr)
{
    int i;
    u_int scale;

    if (p == q) return NULL;
    pwr->present = *p;
    pwr->flags = 0;
    p++;
    for (i = 0; i < 7; i++)
	if (pwr->present & (1<<i)) {
	    if (p == q) return NULL;
	    pwr->param[i] = POWER_CVT(*p);
	    scale = POWER_SCALE(*p);
	    while (*p & 0x80) {
		if (++p == q) return NULL;
		if ((*p & 0x7f) < 100)
		    pwr->param[i] += (*p & 0x7f) * scale / 100;
		else if (*p == 0x7d)
		    pwr->flags |= CISTPL_POWER_HIGHZ_OK;
		else if (*p == 0x7e)
		    pwr->param[i] = 0;
		else if (*p == 0x7f)
		    pwr->flags |= CISTPL_POWER_HIGHZ_REQ;
		else
		    return NULL;
	    }
	    p++;
	}
    return p;
}