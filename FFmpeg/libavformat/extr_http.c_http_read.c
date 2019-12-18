#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {scalar_t__ icy_metaint; int icy_data_read; } ;
typedef  TYPE_2__ HTTPContext ;

/* Variables and functions */
 int http_read_stream (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int store_icy (TYPE_1__*,int) ; 

__attribute__((used)) static int http_read(URLContext *h, uint8_t *buf, int size)
{
    HTTPContext *s = h->priv_data;

    if (s->icy_metaint > 0) {
        size = store_icy(h, size);
        if (size < 0)
            return size;
    }

    size = http_read_stream(h, buf, size);
    if (size > 0)
        s->icy_data_read += size;
    return size;
}