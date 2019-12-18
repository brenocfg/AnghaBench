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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RL16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crc_2D ; 

uint16_t ff_mlp_checksum16(const uint8_t *buf, unsigned int buf_size)
{
    uint16_t crc;

    crc = av_crc(crc_2D, 0, buf, buf_size - 2);
    crc ^= AV_RL16(buf + buf_size - 2);
    return crc;
}