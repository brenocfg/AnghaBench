#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 scalar_t__ IS_MARKER (scalar_t__) ; 
 scalar_t__ VC1_CODE_ENTRYPOINT ; 
 scalar_t__ VC1_CODE_SEQHDR ; 
 int /*<<< orphan*/ * avpriv_find_start_code (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__*) ; 

__attribute__((used)) static int vc1_split(AVCodecContext *avctx,
                           const uint8_t *buf, int buf_size)
{
    uint32_t state = -1;
    int charged = 0;
    const uint8_t *ptr = buf, *end = buf + buf_size;

    while (ptr < end) {
        ptr = avpriv_find_start_code(ptr, end, &state);
        if (state == VC1_CODE_SEQHDR || state == VC1_CODE_ENTRYPOINT) {
            charged = 1;
        } else if (charged && IS_MARKER(state))
            return ptr - 4 - buf;
    }

    return 0;
}