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
struct TYPE_4__ {int /*<<< orphan*/  sigvalue; int /*<<< orphan*/  signal; } ;
typedef  TYPE_1__ asysigs_t ;

/* Variables and functions */
 int /*<<< orphan*/  SG_DTR ; 
 int /*<<< orphan*/  SG_RTS ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stli_mkasysigs(asysigs_t *sp, int dtr, int rts)
{
	memset(sp, 0, sizeof(asysigs_t));
	if (dtr >= 0) {
		sp->signal |= SG_DTR;
		sp->sigvalue |= ((dtr > 0) ? SG_DTR : 0);
	}
	if (rts >= 0) {
		sp->signal |= SG_RTS;
		sp->sigvalue |= ((rts > 0) ? SG_RTS : 0);
	}
}