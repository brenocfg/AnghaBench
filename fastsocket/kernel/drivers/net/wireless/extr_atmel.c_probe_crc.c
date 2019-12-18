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
typedef  int u32 ;
typedef  int u16 ;
struct atmel_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR ; 
 int /*<<< orphan*/  atmel_copy_to_host (int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  atmel_read8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_writeAR (int /*<<< orphan*/ ,int) ; 
 int crc32_le (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int probe_crc(struct atmel_private *priv, u16 packet_loc, u16 msdu_size)
{
	int i = msdu_size - 4;
	u32 netcrc, crc = 0xffffffff;

	if (msdu_size < 4)
		return 0;

	atmel_copy_to_host(priv->dev, (void *)&netcrc, packet_loc + i, 4);

	atmel_writeAR(priv->dev, packet_loc);
	while (i--) {
		u8 octet = atmel_read8(priv->dev, DR);
		crc = crc32_le(crc, &octet, 1);
	}

	return (crc ^ 0xffffffff) == netcrc;
}