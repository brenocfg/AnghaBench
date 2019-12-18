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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ ffio_read_varlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mpc8_get_chunk_header(AVIOContext *pb, int *tag, int64_t *size)
{
    int64_t pos;
    pos = avio_tell(pb);
    *tag = avio_rl16(pb);
    *size = ffio_read_varlen(pb);
    *size -= avio_tell(pb) - pos;
}