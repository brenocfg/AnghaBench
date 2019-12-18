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
struct urb {int dummy; } ;
struct u132_endp {int dummy; } ;
struct u132 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  u132_endp_put_kref (struct u132*,struct u132_endp*) ; 

__attribute__((used)) static void u132_hcd_forget_urb(struct u132 *u132, struct u132_endp *endp,
	struct urb *urb, int status)
{
	u132_endp_put_kref(u132, endp);
}