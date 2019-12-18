#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* cda; void* count; } ;
struct qeth_channel {TYPE_1__ ccw; int /*<<< orphan*/  ccwdev; } ;
struct qeth_card {struct qeth_channel read; } ;
struct ccw1 {int dummy; } ;
typedef  void* __u32 ;

/* Variables and functions */
 struct qeth_card* CARD_FROM_CDEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  READ_CCW ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WRITE_CCW ; 
 scalar_t__ __pa (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qeth_setup_ccw(struct qeth_channel *channel, unsigned char *iob,
		__u32 len)
{
	struct qeth_card *card;

	QETH_DBF_TEXT(TRACE, 4, "setupccw");
	card = CARD_FROM_CDEV(channel->ccwdev);
	if (channel == &card->read)
		memcpy(&channel->ccw, READ_CCW, sizeof(struct ccw1));
	else
		memcpy(&channel->ccw, WRITE_CCW, sizeof(struct ccw1));
	channel->ccw.count = len;
	channel->ccw.cda = (__u32) __pa(iob);
}