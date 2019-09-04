#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  compressor ;
struct TYPE_4__ {int /*<<< orphan*/  destroy; int /*<<< orphan*/  decompress; int /*<<< orphan*/  compress; int /*<<< orphan*/ * context; } ;
typedef  int /*<<< orphan*/  ENetHost ;
typedef  TYPE_1__ ENetCompressor ;

/* Variables and functions */
 int /*<<< orphan*/  enet_host_compress (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  enet_range_coder_compress ; 
 int /*<<< orphan*/ * enet_range_coder_create () ; 
 int /*<<< orphan*/  enet_range_coder_decompress ; 
 int /*<<< orphan*/  enet_range_coder_destroy ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int
enet_host_compress_with_range_coder (ENetHost * host)
{
    ENetCompressor compressor;
    memset (& compressor, 0, sizeof (compressor));
    compressor.context = enet_range_coder_create();
    if (compressor.context == NULL)
      return -1;
    compressor.compress = enet_range_coder_compress;
    compressor.decompress = enet_range_coder_decompress;
    compressor.destroy = enet_range_coder_destroy;
    enet_host_compress (host, & compressor);
    return 0;
}