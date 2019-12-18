#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {int /*<<< orphan*/  udplite_coverage; } ;
typedef  TYPE_2__ UDPContext ;

/* Variables and functions */
 int /*<<< orphan*/  UDP_HEADER_SIZE ; 
 int udp_open (TYPE_1__*,char const*,int) ; 

__attribute__((used)) static int udplite_open(URLContext *h, const char *uri, int flags)
{
    UDPContext *s = h->priv_data;

    // set default checksum coverage
    s->udplite_coverage = UDP_HEADER_SIZE;

    return udp_open(h, uri, flags);
}