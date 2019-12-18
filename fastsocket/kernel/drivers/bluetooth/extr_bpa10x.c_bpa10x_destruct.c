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
struct hci_dev {int /*<<< orphan*/  name; struct bpa10x_data* driver_data; } ;
struct bpa10x_data {int /*<<< orphan*/ * rx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bpa10x_data*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bpa10x_destruct(struct hci_dev *hdev)
{
	struct bpa10x_data *data = hdev->driver_data;

	BT_DBG("%s", hdev->name);

	kfree_skb(data->rx_skb[0]);
	kfree_skb(data->rx_skb[1]);
	kfree(data);
}