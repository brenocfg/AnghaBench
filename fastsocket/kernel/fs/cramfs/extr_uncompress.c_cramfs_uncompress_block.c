#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int avail_in; int avail_out; int total_out; void* next_out; void* next_in; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  printk (char*,void*,...) ; 
 TYPE_1__ stream ; 
 int zlib_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_inflateEnd (TYPE_1__*) ; 
 int /*<<< orphan*/  zlib_inflateInit (TYPE_1__*) ; 
 int zlib_inflateReset (TYPE_1__*) ; 

int cramfs_uncompress_block(void *dst, int dstlen, void *src, int srclen)
{
	int err;

	stream.next_in = src;
	stream.avail_in = srclen;

	stream.next_out = dst;
	stream.avail_out = dstlen;

	err = zlib_inflateReset(&stream);
	if (err != Z_OK) {
		printk("zlib_inflateReset error %d\n", err);
		zlib_inflateEnd(&stream);
		zlib_inflateInit(&stream);
	}

	err = zlib_inflate(&stream, Z_FINISH);
	if (err != Z_STREAM_END)
		goto err;
	return stream.total_out;

err:
	printk("Error %d while decompressing!\n", err);
	printk("%p(%d)->%p(%d)\n", src, srclen, dst, dstlen);
	return -EIO;
}