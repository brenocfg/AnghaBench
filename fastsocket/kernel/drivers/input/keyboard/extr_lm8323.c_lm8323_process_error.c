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
typedef  int u8 ;
struct lm8323_chip {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ERR_BADPAR ; 
 int ERR_CMDUNK ; 
 int ERR_FIFOOVER ; 
 int ERR_KEYOVR ; 
 int /*<<< orphan*/  LM8323_CMD_READ_ERR ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*) ; 
 int lm8323_read (struct lm8323_chip*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void lm8323_process_error(struct lm8323_chip *lm)
{
	u8 error;

	if (lm8323_read(lm, LM8323_CMD_READ_ERR, &error, 1) == 1) {
		if (error & ERR_FIFOOVER)
			dev_vdbg(&lm->client->dev, "fifo overflow!\n");
		if (error & ERR_KEYOVR)
			dev_vdbg(&lm->client->dev,
					"more than two keys pressed\n");
		if (error & ERR_CMDUNK)
			dev_vdbg(&lm->client->dev,
					"unknown command submitted\n");
		if (error & ERR_BADPAR)
			dev_vdbg(&lm->client->dev, "bad command parameter\n");
	}
}