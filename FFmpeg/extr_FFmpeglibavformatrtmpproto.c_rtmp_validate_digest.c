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

/* Variables and functions */
 int /*<<< orphan*/  RTMP_HANDSHAKE_PACKET_SIZE ; 
 int /*<<< orphan*/  SERVER_KEY_OPEN_PART_LEN ; 
 int ff_rtmp_calc_digest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_rtmp_calc_digest_pos (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtmp_server_key ; 

__attribute__((used)) static int rtmp_validate_digest(uint8_t *buf, int off)
{
    uint8_t digest[32];
    int ret, digest_pos;

    digest_pos = ff_rtmp_calc_digest_pos(buf, off, 728, off + 4);

    ret = ff_rtmp_calc_digest(buf, RTMP_HANDSHAKE_PACKET_SIZE, digest_pos,
                              rtmp_server_key, SERVER_KEY_OPEN_PART_LEN,
                              digest);
    if (ret < 0)
        return ret;

    if (!memcmp(digest, buf + digest_pos, 32))
        return digest_pos;
    return 0;
}