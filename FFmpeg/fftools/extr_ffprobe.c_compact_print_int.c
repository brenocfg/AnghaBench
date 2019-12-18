#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t level; TYPE_1__* section_pbuf; scalar_t__* nb_item; TYPE_3__* priv; } ;
typedef  TYPE_2__ WriterContext ;
struct TYPE_7__ {long long item_sep; int /*<<< orphan*/  nokey; } ;
struct TYPE_5__ {char* str; } ;
typedef  TYPE_3__ CompactContext ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void compact_print_int(WriterContext *wctx, const char *key, long long int value)
{
    CompactContext *compact = wctx->priv;

    if (wctx->nb_item[wctx->level]) printf("%c", compact->item_sep);
    if (!compact->nokey)
        printf("%s%s=", wctx->section_pbuf[wctx->level].str, key);
    printf("%lld", value);
}