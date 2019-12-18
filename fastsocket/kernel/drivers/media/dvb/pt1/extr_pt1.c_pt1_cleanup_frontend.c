#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pt1_adapter {int /*<<< orphan*/  fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_unregister_frontend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pt1_cleanup_frontend(struct pt1_adapter *adap)
{
	dvb_unregister_frontend(adap->fe);
}