#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int buf_count; } ;
struct TYPE_4__ {int buf_count; } ;
struct TYPE_6__ {TYPE_2__ init_pool; TYPE_1__ in_buf_pool; } ;
struct qeth_card {scalar_t__ state; TYPE_3__ qdio; } ;

/* Variables and functions */
 scalar_t__ CARD_STATE_DOWN ; 
 scalar_t__ CARD_STATE_RECOVER ; 
 int EPERM ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int qeth_alloc_buffer_pool (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_clear_working_pool_list (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_free_buffer_pool (struct qeth_card*) ; 

int qeth_realloc_buffer_pool(struct qeth_card *card, int bufcnt)
{
	QETH_DBF_TEXT(TRACE, 2, "realcbp");

	if ((card->state != CARD_STATE_DOWN) &&
	    (card->state != CARD_STATE_RECOVER))
		return -EPERM;

	/* TODO: steel/add buffers from/to a running card's buffer pool (?) */
	qeth_clear_working_pool_list(card);
	qeth_free_buffer_pool(card);
	card->qdio.in_buf_pool.buf_count = bufcnt;
	card->qdio.init_pool.buf_count = bufcnt;
	return qeth_alloc_buffer_pool(card);
}