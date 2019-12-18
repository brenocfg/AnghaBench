#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pl; int /*<<< orphan*/  pi; } ;
typedef  TYPE_1__ irda_param_t ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  PV_TYPE ;
typedef  int (* PI_HANDLER ) (void*,TYPE_1__*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  PV_GET ; 
 int /*<<< orphan*/  irda_param_pack (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int stub1 (void*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int irda_insert_no_value(void *self, __u8 *buf, int len, __u8 pi,
				PV_TYPE type, PI_HANDLER func)
{
	irda_param_t p;
	int ret;

	p.pi = pi;
	p.pl = 0;

	/* Call handler for this parameter */
	ret = (*func)(self, &p, PV_GET);

	/* Extract values anyway, since handler may need them */
	irda_param_pack(buf, "bb", p.pi, p.pl);

	if (ret < 0)
		return ret;

	return 2; /* Inserted pl+2 bytes */
}