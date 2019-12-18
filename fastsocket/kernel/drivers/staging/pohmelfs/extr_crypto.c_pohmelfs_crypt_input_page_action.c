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
struct TYPE_4__ {int /*<<< orphan*/  iv; int /*<<< orphan*/  data; } ;
struct pohmelfs_crypto_thread {int /*<<< orphan*/  page; TYPE_1__ eng; int /*<<< orphan*/  size; TYPE_3__* psb; } ;
struct pohmelfs_crypto_input_action_data {int /*<<< orphan*/  page; int /*<<< orphan*/  iv; int /*<<< orphan*/  size; TYPE_2__* e; } ;
struct TYPE_6__ {int /*<<< orphan*/  crypto_attached_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pohmelfs_crypt_input_page_action(struct pohmelfs_crypto_thread *t, void *data)
{
	struct pohmelfs_crypto_input_action_data *act = data;

	memcpy(t->eng.data, act->e->data, t->psb->crypto_attached_size);

	t->size = act->size;
	t->eng.iv = act->iv;

	t->page = act->page;
	return 0;
}