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
typedef  int /*<<< orphan*/  uint32_t ;
struct radio_data {scalar_t__ users; scalar_t__ is_radio_streaming; } ;
struct poseidon {int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; int /*<<< orphan*/  interface; struct file* file_for_stream; int /*<<< orphan*/  state; struct radio_data radio_data; } ;
struct file {struct poseidon* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLAY_SERVICE ; 
 int /*<<< orphan*/  POSEIDON_STATE_FM ; 
 int /*<<< orphan*/  TLG_TUNE_PLAY_SVC_STOP ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poseidon_delete ; 
 int /*<<< orphan*/  send_set_req (struct poseidon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int poseidon_fm_close(struct file *filp)
{
	struct poseidon *p = filp->private_data;
	struct radio_data *fm = &p->radio_data;
	uint32_t status;

	mutex_lock(&p->lock);
	fm->users--;
	if (0 == fm->users)
		p->state &= ~POSEIDON_STATE_FM;

	if (fm->is_radio_streaming && filp == p->file_for_stream) {
		fm->is_radio_streaming = 0;
		send_set_req(p, PLAY_SERVICE, TLG_TUNE_PLAY_SVC_STOP, &status);
	}
	usb_autopm_put_interface(p->interface);
	mutex_unlock(&p->lock);

	kref_put(&p->kref, poseidon_delete);
	filp->private_data = NULL;
	return 0;
}