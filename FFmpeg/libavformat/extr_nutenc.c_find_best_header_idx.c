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
struct TYPE_6__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int header_count; int* header_len; int /*<<< orphan*/ * header; } ;
typedef  TYPE_1__ NUTContext ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int find_best_header_idx(NUTContext *nut, AVPacket *pkt)
{
    int i;
    int best_i   = 0;
    int best_len = 0;

    if (pkt->size > 4096)
        return 0;

    for (i = 1; i < nut->header_count; i++)
        if (pkt->size >= nut->header_len[i]
            && nut->header_len[i] > best_len
            && !memcmp(pkt->data, nut->header[i], nut->header_len[i])) {
            best_i   = i;
            best_len = nut->header_len[i];
        }
    return best_i;
}