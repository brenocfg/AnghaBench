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
struct vc_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int newport_scrolldelta(struct vc_data *vc, int lines)
{
	/* there is (nearly) no off-screen memory, so we can't scroll back */
	return 0;
}