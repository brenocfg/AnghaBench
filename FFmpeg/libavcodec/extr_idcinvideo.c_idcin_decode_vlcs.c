#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* children; } ;
typedef  TYPE_1__ hnode ;
struct TYPE_10__ {long height; long width; } ;
struct TYPE_9__ {long* linesize; int** data; } ;
struct TYPE_8__ {int* num_huff_nodes; int size; unsigned char* buf; TYPE_6__* avctx; TYPE_1__** huff_nodes; } ;
typedef  TYPE_2__ IdcinContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int HUF_TOKENS ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int idcin_decode_vlcs(IdcinContext *s, AVFrame *frame)
{
    hnode *hnodes;
    long x, y;
    int prev;
    unsigned char v = 0;
    int bit_pos, node_num, dat_pos;

    prev = bit_pos = dat_pos = 0;
    for (y = 0; y < (frame->linesize[0] * s->avctx->height);
        y += frame->linesize[0]) {
        for (x = y; x < y + s->avctx->width; x++) {
            node_num = s->num_huff_nodes[prev];
            hnodes = s->huff_nodes[prev];

            while(node_num >= HUF_TOKENS) {
                if(!bit_pos) {
                    if(dat_pos >= s->size) {
                        av_log(s->avctx, AV_LOG_ERROR, "Huffman decode error.\n");
                        return -1;
                    }
                    bit_pos = 8;
                    v = s->buf[dat_pos++];
                }

                node_num = hnodes[node_num].children[v & 0x01];
                v = v >> 1;
                bit_pos--;
            }

            frame->data[0][x] = node_num;
            prev = node_num;
        }
    }

    return 0;
}