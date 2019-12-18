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
struct tty {int dummy; } ;
struct label {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tty*,int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  pty_notify_grant ; 

void
mac_pty_notify_grant(proc_t p, struct tty *tp, dev_t dev, struct label *label) {
	MAC_PERFORM(pty_notify_grant, p, tp, dev, label);
}