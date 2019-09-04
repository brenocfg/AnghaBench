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
 int /*<<< orphan*/  av_md5_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,scalar_t__) ; 
 int /*<<< orphan*/  md5 ; 
 scalar_t__ out ; 
 int out_size ; 

__attribute__((used)) static int io_write(void *opaque, uint8_t *buf, int size)
{
    out_size += size;
    av_md5_update(md5, buf, size);
    if (out)
        fwrite(buf, 1, size, out);
    return size;
}