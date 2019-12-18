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
struct i2400m_msg_hdr {int /*<<< orphan*/  num_pls; } ;
struct i2400m {struct i2400m_msg_hdr* tx_msg; } ;

/* Variables and functions */
 scalar_t__ I2400M_TX_PLD_MAX ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
unsigned i2400m_tx_fits(struct i2400m *i2400m)
{
	struct i2400m_msg_hdr *msg_hdr = i2400m->tx_msg;
	return le16_to_cpu(msg_hdr->num_pls) < I2400M_TX_PLD_MAX;

}