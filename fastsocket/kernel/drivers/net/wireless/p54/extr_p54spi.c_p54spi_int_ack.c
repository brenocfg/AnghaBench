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
typedef  int /*<<< orphan*/  u32 ;
struct p54s_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_ADRS_HOST_INT_ACK ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54spi_write32 (struct p54s_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void p54spi_int_ack(struct p54s_priv *priv, u32 val)
{
	p54spi_write32(priv, SPI_ADRS_HOST_INT_ACK, cpu_to_le32(val));
}