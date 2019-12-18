#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ invert6; scalar_t__ invert4; scalar_t__ enabled; int /*<<< orphan*/  entries; } ;
struct TYPE_7__ {void* state; } ;
struct TYPE_6__ {void* state; } ;
struct TYPE_5__ {void* state; } ;
struct qeth_card {int /*<<< orphan*/  close_dev_work; int /*<<< orphan*/  buffer_reclaim_work; TYPE_4__ ipato; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  cmd_waiter_list; int /*<<< orphan*/ * ip_tbd_list; int /*<<< orphan*/  ip_list; int /*<<< orphan*/  kernel_thread_starter; scalar_t__ thread_running_mask; scalar_t__ thread_allowed_mask; scalar_t__ thread_start_mask; int /*<<< orphan*/  discipline_mutex; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  thread_mask_lock; int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/ * vlangrp; int /*<<< orphan*/  mclock; int /*<<< orphan*/  vlanlock; int /*<<< orphan*/ * dev; scalar_t__ read_or_write_problem; scalar_t__ lan_online; int /*<<< orphan*/  state; TYPE_3__ data; TYPE_2__ write; TYPE_1__ read; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_STATE_DOWN ; 
 void* CH_STATE_DOWN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct qeth_card**,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_buffer_reclaim_work ; 
 int /*<<< orphan*/  qeth_close_dev_handler ; 
 int /*<<< orphan*/  qeth_init_qdio_info (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_set_intial_options (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_start_kernel_thread ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_setup_card(struct qeth_card *card)
{

	QETH_DBF_TEXT(SETUP, 2, "setupcrd");
	QETH_DBF_HEX(SETUP, 2, &card, sizeof(void *));

	card->read.state  = CH_STATE_DOWN;
	card->write.state = CH_STATE_DOWN;
	card->data.state  = CH_STATE_DOWN;
	card->state = CARD_STATE_DOWN;
	card->lan_online = 0;
	card->read_or_write_problem = 0;
	card->dev = NULL;
	spin_lock_init(&card->vlanlock);
	spin_lock_init(&card->mclock);
	card->vlangrp = NULL;
	spin_lock_init(&card->lock);
	spin_lock_init(&card->ip_lock);
	spin_lock_init(&card->thread_mask_lock);
	mutex_init(&card->conf_mutex);
	mutex_init(&card->discipline_mutex);
	card->thread_start_mask = 0;
	card->thread_allowed_mask = 0;
	card->thread_running_mask = 0;
	INIT_WORK(&card->kernel_thread_starter, qeth_start_kernel_thread);
	INIT_LIST_HEAD(&card->ip_list);
	INIT_LIST_HEAD(card->ip_tbd_list);
	INIT_LIST_HEAD(&card->cmd_waiter_list);
	init_waitqueue_head(&card->wait_q);
	/* intial options */
	qeth_set_intial_options(card);
	/* IP address takeover */
	INIT_LIST_HEAD(&card->ipato.entries);
	card->ipato.enabled = 0;
	card->ipato.invert4 = 0;
	card->ipato.invert6 = 0;
	/* init QDIO stuff */
	qeth_init_qdio_info(card);
	INIT_DELAYED_WORK(&card->buffer_reclaim_work, qeth_buffer_reclaim_work);
	INIT_WORK(&card->close_dev_work, qeth_close_dev_handler);
	return 0;
}