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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_3__ {int buf_size; int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RL16 (int*) ; 
 int AV_RL24 (int*) ; 
 int FF_ARRAY_ELEMS (int*) ; 
 scalar_t__ IS_16LE_MARKER (int) ; 
 scalar_t__ IS_20LE_MARKER (int) ; 
 int /*<<< orphan*/  IS_LE_MARKER (int) ; 
 scalar_t__ s337m_get_offset_and_codec (int /*<<< orphan*/ *,int,int,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s337m_probe(const AVProbeData *p)
{
    uint64_t state = 0;
    int markers[3] = { 0 };
    int i, pos, sum, max, data_type, data_size, offset;
    uint8_t *buf;

    for (pos = 0; pos < p->buf_size; pos++) {
        state = (state << 8) | p->buf[pos];
        if (!IS_LE_MARKER(state))
            continue;

        buf = p->buf + pos + 1;
        if (IS_16LE_MARKER(state)) {
            data_type = AV_RL16(buf    );
            data_size = AV_RL16(buf + 2);
        } else {
            data_type = AV_RL24(buf    );
            data_size = AV_RL24(buf + 3);
        }

        if (s337m_get_offset_and_codec(NULL, state, data_type, data_size, &offset, NULL))
            continue;

        i = IS_16LE_MARKER(state) ? 0 : IS_20LE_MARKER(state) ? 1 : 2;
        markers[i]++;

        pos  += IS_16LE_MARKER(state) ? 4 : 6;
        pos  += offset;
        state = 0;
    }

    sum = max = 0;
    for (i = 0; i < FF_ARRAY_ELEMS(markers); i++) {
        sum += markers[i];
        if (markers[max] < markers[i])
            max = i;
    }

    if (markers[max] > 3 && markers[max] * 4 > sum * 3)
        return AVPROBE_SCORE_EXTENSION + 1;

    return 0;
}