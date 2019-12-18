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
struct firedtv {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ avc_ca_reset (struct firedtv*) ; 

__attribute__((used)) static int fdtv_ca_reset(struct firedtv *fdtv)
{
	return avc_ca_reset(fdtv) ? -EFAULT : 0;
}