#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ id; int /*<<< orphan*/  extract; } ;
struct TYPE_9__ {TYPE_1__* par_in; TYPE_2__* priv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  extract; } ;
struct TYPE_7__ {scalar_t__ codec_id; } ;
typedef  TYPE_2__ ExtractExtradataContext ;
typedef  TYPE_3__ AVBSFContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int FF_ARRAY_ELEMS (TYPE_4__*) ; 
 TYPE_4__* extract_tab ; 

__attribute__((used)) static int extract_extradata_init(AVBSFContext *ctx)
{
    ExtractExtradataContext *s = ctx->priv_data;
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(extract_tab); i++) {
        if (extract_tab[i].id == ctx->par_in->codec_id) {
            s->extract = extract_tab[i].extract;
            break;
        }
    }
    if (!s->extract)
        return AVERROR_BUG;

    return 0;
}