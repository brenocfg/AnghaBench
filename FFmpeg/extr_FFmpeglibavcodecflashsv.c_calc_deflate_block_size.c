#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* opaque; void* zfree; void* zalloc; } ;
typedef  TYPE_1__ z_stream ;

/* Variables and functions */
 void* Z_NULL ; 
 scalar_t__ Z_OK ; 
 int deflateBound (TYPE_1__*,int) ; 
 int /*<<< orphan*/  deflateEnd (TYPE_1__*) ; 
 scalar_t__ deflateInit (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int calc_deflate_block_size(int tmpblock_size)
{
    z_stream zstream;
    int size;

    zstream.zalloc = Z_NULL;
    zstream.zfree  = Z_NULL;
    zstream.opaque = Z_NULL;
    if (deflateInit(&zstream, 0) != Z_OK)
        return -1;
    size = deflateBound(&zstream, tmpblock_size);
    deflateEnd(&zstream);

    return size;
}