#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ num_rows; } ;
struct TYPE_15__ {scalar_t__ table; } ;
struct TYPE_14__ {int num_rows; void** xbits; } ;
struct TYPE_13__ {int tab_sel; TYPE_3__* tab; TYPE_3__ cust_tab; TYPE_4__ cust_desc; } ;
typedef  TYPE_1__ IVIHuffTab ;
typedef  TYPE_2__ IVIHuffDesc ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_free_vlc (TYPE_3__*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* ivi_blk_vlc_tabs ; 
 int ivi_create_huff_from_desc (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ivi_huff_desc_cmp (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ivi_huff_desc_copy (TYPE_4__*,TYPE_2__*) ; 
 TYPE_3__* ivi_mb_vlc_tabs ; 

int ff_ivi_dec_huff_desc(GetBitContext *gb, int desc_coded, int which_tab,
                         IVIHuffTab *huff_tab, AVCodecContext *avctx)
{
    int i, result;
    IVIHuffDesc new_huff;

    if (!desc_coded) {
        /* select default table */
        huff_tab->tab = (which_tab) ? &ivi_blk_vlc_tabs[7]
                                    : &ivi_mb_vlc_tabs [7];
        return 0;
    }

    huff_tab->tab_sel = get_bits(gb, 3);
    if (huff_tab->tab_sel == 7) {
        /* custom huffman table (explicitly encoded) */
        new_huff.num_rows = get_bits(gb, 4);
        if (!new_huff.num_rows) {
            av_log(avctx, AV_LOG_ERROR, "Empty custom Huffman table!\n");
            return AVERROR_INVALIDDATA;
        }

        for (i = 0; i < new_huff.num_rows; i++)
            new_huff.xbits[i] = get_bits(gb, 4);

        /* Have we got the same custom table? Rebuild if not. */
        if (ivi_huff_desc_cmp(&new_huff, &huff_tab->cust_desc) || !huff_tab->cust_tab.table) {
            ivi_huff_desc_copy(&huff_tab->cust_desc, &new_huff);

            if (huff_tab->cust_tab.table)
                ff_free_vlc(&huff_tab->cust_tab);
            result = ivi_create_huff_from_desc(&huff_tab->cust_desc,
                    &huff_tab->cust_tab, 0);
            if (result) {
                // reset faulty description
                huff_tab->cust_desc.num_rows = 0;
                av_log(avctx, AV_LOG_ERROR,
                       "Error while initializing custom vlc table!\n");
                return result;
            }
        }
        huff_tab->tab = &huff_tab->cust_tab;
    } else {
        /* select one of predefined tables */
        huff_tab->tab = (which_tab) ? &ivi_blk_vlc_tabs[huff_tab->tab_sel]
            : &ivi_mb_vlc_tabs [huff_tab->tab_sel];
    }

    return 0;
}