#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int header_count; int* header_len; int /*<<< orphan*/ * header; } ;
typedef  TYPE_1__ NUTContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVCodecParameters ;

/* Variables and functions */
 int find_expected_header (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int find_header_idx(AVFormatContext *s, AVCodecParameters *p, int size,
                           int frame_type)
{
    NUTContext *nut = s->priv_data;
    uint8_t out[64];
    int i;
    int len = find_expected_header(p, size, frame_type, out);

    for (i = 1; i < nut->header_count; i++) {
        if (len == nut->header_len[i] && !memcmp(out, nut->header[i], len)) {
            return i;
        }
    }

    return 0;
}