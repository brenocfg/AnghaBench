#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ next_in; scalar_t__ avail_in; int avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * opaque; int /*<<< orphan*/ * zfree; int /*<<< orphan*/ * zalloc; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {scalar_t__ enc; scalar_t__ enc_size; scalar_t__ sl_begin; scalar_t__ sl_end; } ;
typedef  TYPE_2__ Block ;

/* Variables and functions */
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deflateEnd (TYPE_1__*) ; 
 int deflateInit (TYPE_1__*,int) ; 

__attribute__((used)) static int encode_zlibprime(Block * b, Block * prime, uint8_t * buf,
                            int *buf_size, int comp)
{
    z_stream s;
    int res;
    s.zalloc = NULL;
    s.zfree  = NULL;
    s.opaque = NULL;
    res = deflateInit(&s, comp);
    if (res < 0)
        return -1;

    s.next_in  = prime->enc;
    s.avail_in = prime->enc_size;
    while (s.avail_in > 0) {
        s.next_out  = buf;
        s.avail_out = *buf_size;
        res = deflate(&s, Z_SYNC_FLUSH);
        if (res < 0)
            return -1;
    }

    s.next_in   = b->sl_begin;
    s.avail_in  = b->sl_end - b->sl_begin;
    s.next_out  = buf;
    s.avail_out = *buf_size;
    res = deflate(&s, Z_FINISH);
    deflateEnd(&s);
    *buf_size -= s.avail_out;
    if (res != Z_STREAM_END)
        return -1;
    return 0;
}