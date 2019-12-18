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
struct usb_ftdi {scalar_t__ respond_next; scalar_t__ respond_head; int /*<<< orphan*/  u132_lock; struct u132_respond* respond; } ;
struct u132_respond {int /*<<< orphan*/  wait_completion; scalar_t__* value; int /*<<< orphan*/ * result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 size_t RESPOND_MASK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ftdi_elan_abandon_completions(struct usb_ftdi *ftdi)
{
        mutex_lock(&ftdi->u132_lock);
        while (ftdi->respond_next > ftdi->respond_head) {
                struct u132_respond *respond = &ftdi->respond[RESPOND_MASK &
                        ftdi->respond_head++];
                *respond->result = -ESHUTDOWN;
                *respond->value = 0;
                complete(&respond->wait_completion);
        } mutex_unlock(&ftdi->u132_lock);
}