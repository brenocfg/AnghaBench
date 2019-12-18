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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_4__ {int frame_start_found; int state64; } ;
struct TYPE_5__ {int size; scalar_t__ lastmarker; int startpos; int framesize; TYPE_1__ pc; } ;
typedef  TYPE_1__ ParseContext ;
typedef  TYPE_2__ DCAParseContext ;

/* Variables and functions */
 void* CORE_FRAMESIZE (int) ; 
 scalar_t__ CORE_MARKER (int) ; 
#define  DCA_SYNCWORD_CORE_14B_BE 132 
#define  DCA_SYNCWORD_CORE_14B_LE 131 
#define  DCA_SYNCWORD_CORE_BE 130 
#define  DCA_SYNCWORD_CORE_LE 129 
#define  DCA_SYNCWORD_SUBSTREAM 128 
 int END_NOT_FOUND ; 
 int EXSS_FRAMESIZE (int) ; 
 int EXSS_MARKER (int) ; 
 scalar_t__ IS_EXSS_MARKER (int) ; 
 scalar_t__ IS_MARKER (int) ; 
 int STATE_14 (int) ; 
 int STATE_LE (int) ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dca_find_frame_end(DCAParseContext *pc1, const uint8_t *buf,
                              int buf_size)
{
    int start_found, size, i;
    uint64_t state;
    ParseContext *pc = &pc1->pc;

    start_found = pc->frame_start_found;
    state       = pc->state64;
    size        = pc1->size;

    i = 0;
    if (!start_found) {
        for (; i < buf_size; i++) {
            size++;
            state = (state << 8) | buf[i];

            if (IS_MARKER(state) &&
                (!pc1->lastmarker ||
                  pc1->lastmarker == CORE_MARKER(state) ||
                  pc1->lastmarker == DCA_SYNCWORD_SUBSTREAM)) {
                if (!pc1->lastmarker)
                    pc1->startpos = IS_EXSS_MARKER(state) ? size - 4 : size - 6;

                if (IS_EXSS_MARKER(state))
                    pc1->lastmarker = EXSS_MARKER(state);
                else
                    pc1->lastmarker = CORE_MARKER(state);

                start_found = 1;
                size        = 0;

                i++;
                break;
            }
        }
    }

    if (start_found) {
        for (; i < buf_size; i++) {
            size++;
            state = (state << 8) | buf[i];

            if (start_found == 1) {
                switch (pc1->lastmarker) {
                case DCA_SYNCWORD_CORE_BE:
                    if (size == 2) {
                        pc1->framesize = CORE_FRAMESIZE(state);
                        start_found    = 2;
                    }
                    break;
                case DCA_SYNCWORD_CORE_LE:
                    if (size == 2) {
                        pc1->framesize = CORE_FRAMESIZE(STATE_LE(state));
                        start_found    = 4;
                    }
                    break;
                case DCA_SYNCWORD_CORE_14B_BE:
                    if (size == 4) {
                        pc1->framesize = CORE_FRAMESIZE(STATE_14(state));
                        start_found    = 4;
                    }
                    break;
                case DCA_SYNCWORD_CORE_14B_LE:
                    if (size == 4) {
                        pc1->framesize = CORE_FRAMESIZE(STATE_14(STATE_LE(state)));
                        start_found    = 4;
                    }
                    break;
                case DCA_SYNCWORD_SUBSTREAM:
                    if (size == 6) {
                        pc1->framesize = EXSS_FRAMESIZE(state);
                        start_found    = 4;
                    }
                    break;
                default:
                    av_assert0(0);
                }
                continue;
            }

            if (start_found == 2 && IS_EXSS_MARKER(state) &&
                pc1->framesize <= size + 2) {
                pc1->framesize  = size + 2;
                start_found     = 3;
                continue;
            }

            if (start_found == 3) {
                if (size == pc1->framesize + 4) {
                    pc1->framesize += EXSS_FRAMESIZE(state);
                    start_found     = 4;
                }
                continue;
            }

            if (pc1->framesize > size)
                continue;

            if (IS_MARKER(state) &&
                (pc1->lastmarker == CORE_MARKER(state) ||
                 pc1->lastmarker == DCA_SYNCWORD_SUBSTREAM)) {
                pc->frame_start_found = 0;
                pc->state64           = -1;
                pc1->size             = 0;
                return IS_EXSS_MARKER(state) ? i - 3 : i - 5;
            }
        }
    }

    pc->frame_start_found = start_found;
    pc->state64           = state;
    pc1->size             = size;
    return END_NOT_FOUND;
}