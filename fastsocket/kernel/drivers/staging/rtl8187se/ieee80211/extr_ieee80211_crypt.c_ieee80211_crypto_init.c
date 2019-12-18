#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  algs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* hcrypt ; 
 int /*<<< orphan*/  ieee80211_crypt_null ; 
 int ieee80211_register_crypto_ops (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ieee80211_crypto_init(void)
{
	int ret = -ENOMEM;

	hcrypt = kmalloc(sizeof(*hcrypt), GFP_KERNEL);
	if (!hcrypt)
		goto out;

	memset(hcrypt, 0, sizeof(*hcrypt));
	INIT_LIST_HEAD(&hcrypt->algs);
	spin_lock_init(&hcrypt->lock);

	ret = ieee80211_register_crypto_ops(&ieee80211_crypt_null);
	if (ret < 0) {
		kfree(hcrypt);
		hcrypt = NULL;
	}
out:
	return ret;
}