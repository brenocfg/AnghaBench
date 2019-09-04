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
struct tcpip_callback_msg {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_VAL ; 
 int /*<<< orphan*/  mbox ; 
 int /*<<< orphan*/  sys_mbox_trypost (int /*<<< orphan*/ *,struct tcpip_callback_msg*) ; 
 int /*<<< orphan*/  sys_mbox_valid (int /*<<< orphan*/ *) ; 

err_t
tcpip_trycallback(struct tcpip_callback_msg* msg)
{
  if (!sys_mbox_valid(&mbox)) {
    return ERR_VAL;
  }
  return sys_mbox_trypost(&mbox, msg);
}