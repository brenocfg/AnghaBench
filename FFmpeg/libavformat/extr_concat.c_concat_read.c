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
struct concat_nodes {int /*<<< orphan*/  uc; } ;
struct concat_data {size_t current; size_t length; struct concat_nodes* nodes; } ;
struct TYPE_3__ {struct concat_data* priv_data; } ;
typedef  TYPE_1__ URLContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int ffurl_read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ ffurl_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int concat_read(URLContext *h, unsigned char *buf, int size)
{
    int result, total = 0;
    struct concat_data  *data  = h->priv_data;
    struct concat_nodes *nodes = data->nodes;
    size_t i                   = data->current;

    while (size > 0) {
        result = ffurl_read(nodes[i].uc, buf, size);
        if (result == AVERROR_EOF) {
            if (i + 1 == data->length ||
                ffurl_seek(nodes[++i].uc, 0, SEEK_SET) < 0)
                break;
            result = 0;
        }
        if (result < 0)
            return total ? total : result;
        total += result;
        buf   += result;
        size  -= result;
    }
    data->current = i;
    return total ? total : result;
}