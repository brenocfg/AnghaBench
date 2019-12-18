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
struct ath9k_htc_rxbuf {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  rxbuf; int /*<<< orphan*/  rxbuflock; } ;
struct ath9k_htc_priv {TYPE_1__ rx; } ;

/* Variables and functions */
 int ATH9K_HTC_RXBUF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_rx_cleanup (struct ath9k_htc_priv*) ; 
 struct ath9k_htc_rxbuf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ath9k_rx_init(struct ath9k_htc_priv *priv)
{
	int i = 0;

	INIT_LIST_HEAD(&priv->rx.rxbuf);
	spin_lock_init(&priv->rx.rxbuflock);

	for (i = 0; i < ATH9K_HTC_RXBUF; i++) {
		struct ath9k_htc_rxbuf *rxbuf =
			kzalloc(sizeof(struct ath9k_htc_rxbuf), GFP_KERNEL);
		if (rxbuf == NULL)
			goto err;

		list_add_tail(&rxbuf->list, &priv->rx.rxbuf);
	}

	return 0;

err:
	ath9k_rx_cleanup(priv);
	return -ENOMEM;
}