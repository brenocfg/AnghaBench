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
struct parport {int dummy; } ;

/* Variables and functions */
 scalar_t__ accept_bwqcam (struct parport*) ; 
 int /*<<< orphan*/  init_bwqcam (struct parport*) ; 

__attribute__((used)) static void bwqcam_attach(struct parport *port)
{
	if (accept_bwqcam(port))
		init_bwqcam(port);
}