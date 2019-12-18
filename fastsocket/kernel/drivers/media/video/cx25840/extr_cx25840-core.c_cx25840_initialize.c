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
struct workqueue_struct {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int /*<<< orphan*/  aud_input; int /*<<< orphan*/  vid_input; int /*<<< orphan*/  fw_wait; int /*<<< orphan*/  fw_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 struct workqueue_struct* create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  cx25840_and_or (struct i2c_client*,int,int,int) ; 
 int /*<<< orphan*/  cx25840_std_setup (struct i2c_client*) ; 
 int /*<<< orphan*/  cx25840_work_handler ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  init_dll1 (struct i2c_client*) ; 
 int /*<<< orphan*/  init_dll2 (struct i2c_client*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (struct workqueue_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_input (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void cx25840_initialize(struct i2c_client *client)
{
	DEFINE_WAIT(wait);
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));
	struct workqueue_struct *q;

	/* datasheet startup in numbered steps, refer to page 3-77 */
	/* 2. */
	cx25840_and_or(client, 0x803, ~0x10, 0x00);
	/* The default of this register should be 4, but I get 0 instead.
	 * Set this register to 4 manually. */
	cx25840_write(client, 0x000, 0x04);
	/* 3. */
	init_dll1(client);
	init_dll2(client);
	cx25840_write(client, 0x136, 0x0a);
	/* 4. */
	cx25840_write(client, 0x13c, 0x01);
	cx25840_write(client, 0x13c, 0x00);
	/* 5. */
	/* Do the firmware load in a work handler to prevent.
	   Otherwise the kernel is blocked waiting for the
	   bit-banging i2c interface to finish uploading the
	   firmware. */
	INIT_WORK(&state->fw_work, cx25840_work_handler);
	init_waitqueue_head(&state->fw_wait);
	q = create_singlethread_workqueue("cx25840_fw");
	prepare_to_wait(&state->fw_wait, &wait, TASK_UNINTERRUPTIBLE);
	queue_work(q, &state->fw_work);
	schedule();
	finish_wait(&state->fw_wait, &wait);
	destroy_workqueue(q);

	/* 6. */
	cx25840_write(client, 0x115, 0x8c);
	cx25840_write(client, 0x116, 0x07);
	cx25840_write(client, 0x118, 0x02);
	/* 7. */
	cx25840_write(client, 0x4a5, 0x80);
	cx25840_write(client, 0x4a5, 0x00);
	cx25840_write(client, 0x402, 0x00);
	/* 8. */
	cx25840_and_or(client, 0x401, ~0x18, 0);
	cx25840_and_or(client, 0x4a2, ~0x10, 0x10);
	/* steps 8c and 8d are done in change_input() */
	/* 10. */
	cx25840_write(client, 0x8d3, 0x1f);
	cx25840_write(client, 0x8e3, 0x03);

	cx25840_std_setup(client);

	/* trial and error says these are needed to get audio */
	cx25840_write(client, 0x914, 0xa0);
	cx25840_write(client, 0x918, 0xa0);
	cx25840_write(client, 0x919, 0x01);

	/* stereo prefered */
	cx25840_write(client, 0x809, 0x04);
	/* AC97 shift */
	cx25840_write(client, 0x8cf, 0x0f);

	/* (re)set input */
	set_input(client, state->vid_input, state->aud_input);

	/* start microcontroller */
	cx25840_and_or(client, 0x803, ~0x10, 0x10);
}