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
typedef  int /*<<< orphan*/  u16 ;
struct bcsp_struct {TYPE_1__* rx_skb; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_be16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 bscp_get_crc(struct bcsp_struct *bcsp)
{
	return get_unaligned_be16(&bcsp->rx_skb->data[bcsp->rx_skb->len - 2]);
}