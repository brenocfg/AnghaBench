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
typedef  size_t u8 ;
struct lm8323_chip {int keys_down; unsigned short* keymap; int /*<<< orphan*/  active_time; int /*<<< orphan*/  idev; scalar_t__ kp_enabled; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  LM8323_CMD_READ_FIFO ; 
 int /*<<< orphan*/  LM8323_FIFO_LEN ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,size_t,char*) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,unsigned short,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int lm8323_ispress (size_t) ; 
 int lm8323_read (struct lm8323_chip*,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm8323_set_active_time (struct lm8323_chip*,int /*<<< orphan*/ ) ; 
 size_t lm8323_whichkey (size_t) ; 

__attribute__((used)) static void process_keys(struct lm8323_chip *lm)
{
	u8 event;
	u8 key_fifo[LM8323_FIFO_LEN + 1];
	int old_keys_down = lm->keys_down;
	int ret;
	int i = 0;

	/*
	 * Read all key events from the FIFO at once. Next READ_FIFO clears the
	 * FIFO even if we didn't read all events previously.
	 */
	ret = lm8323_read(lm, LM8323_CMD_READ_FIFO, key_fifo, LM8323_FIFO_LEN);

	if (ret < 0) {
		dev_err(&lm->client->dev, "Failed reading fifo \n");
		return;
	}
	key_fifo[ret] = 0;

	while ((event = key_fifo[i++])) {
		u8 key = lm8323_whichkey(event);
		int isdown = lm8323_ispress(event);
		unsigned short keycode = lm->keymap[key];

		dev_vdbg(&lm->client->dev, "key 0x%02x %s\n",
			 key, isdown ? "down" : "up");

		if (lm->kp_enabled) {
			input_event(lm->idev, EV_MSC, MSC_SCAN, key);
			input_report_key(lm->idev, keycode, isdown);
			input_sync(lm->idev);
		}

		if (isdown)
			lm->keys_down++;
		else
			lm->keys_down--;
	}

	/*
	 * Errata: We need to ensure that the chip never enters halt mode
	 * during a keypress, so set active time to 0.  When it's released,
	 * we can enter halt again, so set the active time back to normal.
	 */
	if (!old_keys_down && lm->keys_down)
		lm8323_set_active_time(lm, 0);
	if (old_keys_down && !lm->keys_down)
		lm8323_set_active_time(lm, lm->active_time);
}