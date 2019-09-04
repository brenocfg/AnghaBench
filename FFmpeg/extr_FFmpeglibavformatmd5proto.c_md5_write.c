#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct MD5Context {int /*<<< orphan*/  md5; } ;
struct TYPE_3__ {struct MD5Context* priv_data; } ;
typedef  TYPE_1__ URLContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_md5_update (int /*<<< orphan*/ ,unsigned char const*,int) ; 

__attribute__((used)) static int md5_write(URLContext *h, const unsigned char *buf, int size)
{
    struct MD5Context *c = h->priv_data;
    av_md5_update(c->md5, buf, size);
    return size;
}