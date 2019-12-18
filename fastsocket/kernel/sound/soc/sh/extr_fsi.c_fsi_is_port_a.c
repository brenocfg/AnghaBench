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
struct fsi_priv {int dummy; } ;
struct TYPE_2__ {struct fsi_priv fsia; } ;

/* Variables and functions */
 TYPE_1__* master ; 

__attribute__((used)) static int fsi_is_port_a(struct fsi_priv *fsi)
{
	/* return
	 * 1 : port a
	 * 0 : port b
	 */

	if (fsi == &master->fsia)
		return 1;

	return 0;
}