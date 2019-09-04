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
struct TYPE_5__ {size_t level; scalar_t__* nb_item; TYPE_2__* priv; } ;
typedef  TYPE_1__ WriterContext ;
struct TYPE_6__ {char* item_sep; int /*<<< orphan*/  compact; } ;
typedef  TYPE_2__ JSONContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_INDENT () ; 
 int /*<<< orphan*/  json_print_item_str (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void json_print_str(WriterContext *wctx, const char *key, const char *value)
{
    JSONContext *json = wctx->priv;

    if (wctx->nb_item[wctx->level])
        printf("%s", json->item_sep);
    if (!json->compact)
        JSON_INDENT();
    json_print_item_str(wctx, key, value);
}