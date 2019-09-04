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
struct TYPE_6__ {size_t level; TYPE_1__* section_pbuf; TYPE_3__* priv; } ;
typedef  TYPE_2__ WriterContext ;
struct TYPE_7__ {int /*<<< orphan*/  sep; } ;
struct TYPE_5__ {char* str; } ;
typedef  TYPE_3__ FlatContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  av_bprint_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* flat_escape_key_str (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* flat_escape_value_str (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void flat_print_str(WriterContext *wctx, const char *key, const char *value)
{
    FlatContext *flat = wctx->priv;
    AVBPrint buf;

    printf("%s", wctx->section_pbuf[wctx->level].str);
    av_bprint_init(&buf, 1, AV_BPRINT_SIZE_UNLIMITED);
    printf("%s=", flat_escape_key_str(&buf, key, flat->sep));
    av_bprint_clear(&buf);
    printf("\"%s\"\n", flat_escape_value_str(&buf, value));
    av_bprint_finalize(&buf, NULL);
}