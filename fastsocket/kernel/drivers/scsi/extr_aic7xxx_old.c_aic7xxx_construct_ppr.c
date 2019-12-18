#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct aic7xxx_scb {int /*<<< orphan*/  cmd; } ;
struct aic7xxx_host {int msg_len; int /*<<< orphan*/  msg_index; scalar_t__* msg_buf; } ;
struct TYPE_3__ {scalar_t__ options; scalar_t__ width; scalar_t__ offset; scalar_t__ period; } ;
struct TYPE_4__ {TYPE_1__ goal; } ;

/* Variables and functions */
 TYPE_2__* AIC_DEV (int /*<<< orphan*/ ) ; 
 scalar_t__ MSG_EXTENDED ; 
 scalar_t__ MSG_EXT_PPR ; 
 scalar_t__ MSG_EXT_PPR_LEN ; 

__attribute__((used)) static void
aic7xxx_construct_ppr(struct aic7xxx_host *p, struct aic7xxx_scb *scb)
{
  p->msg_buf[p->msg_index++] = MSG_EXTENDED;
  p->msg_buf[p->msg_index++] = MSG_EXT_PPR_LEN;
  p->msg_buf[p->msg_index++] = MSG_EXT_PPR;
  p->msg_buf[p->msg_index++] = AIC_DEV(scb->cmd)->goal.period;
  p->msg_buf[p->msg_index++] = 0;
  p->msg_buf[p->msg_index++] = AIC_DEV(scb->cmd)->goal.offset;
  p->msg_buf[p->msg_index++] = AIC_DEV(scb->cmd)->goal.width;
  p->msg_buf[p->msg_index++] = AIC_DEV(scb->cmd)->goal.options;
  p->msg_len += 8;
}