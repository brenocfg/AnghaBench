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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct spi_transfer {int len; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int dummy; } ;
struct pcap_chip {scalar_t__ buf; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int ezx_pcap_putget(struct pcap_chip *pcap, u32 *data)
{
	struct spi_transfer t;
	struct spi_message m;
	int status;

	memset(&t, 0, sizeof t);
	spi_message_init(&m);
	t.len = sizeof(u32);
	spi_message_add_tail(&t, &m);

	pcap->buf = *data;
	t.tx_buf = (u8 *) &pcap->buf;
	t.rx_buf = (u8 *) &pcap->buf;
	status = spi_sync(pcap->spi, &m);

	if (status == 0)
		*data = pcap->buf;

	return status;
}