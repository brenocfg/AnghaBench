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
struct TYPE_5__ {int /*<<< orphan*/  pl; int /*<<< orphan*/  pi; } ;
typedef  TYPE_1__ irda_param_t ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  PV_TYPE ;
typedef  int (* PI_HANDLER ) (void*,TYPE_1__*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  PV_PUT ; 
 int /*<<< orphan*/  irda_param_unpack (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (void*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int irda_extract_no_value(void *self, __u8 *buf, int len, __u8 pi,
				 PV_TYPE type, PI_HANDLER func)
{
	irda_param_t p;
	int ret;

	/* Extract values anyway, since handler may need them */
	irda_param_unpack(buf, "bb", &p.pi, &p.pl);

	/* Call handler for this parameter */
	ret = (*func)(self, &p, PV_PUT);

	if (ret < 0)
		return ret;

	return 2; /* Extracted pl+2 bytes */
}