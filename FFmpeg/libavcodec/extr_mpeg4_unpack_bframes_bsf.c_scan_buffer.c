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
typedef  char uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int USER_DATA_STARTCODE ; 
 int VOP_STARTCODE ; 
 char* avpriv_find_start_code (char const*,char const*,int*) ; 

__attribute__((used)) static void scan_buffer(const uint8_t *buf, int buf_size,
                        int *pos_p, int *nb_vop, int *pos_vop2) {
    uint32_t startcode;
    const uint8_t *end = buf + buf_size, *pos = buf;

    while (pos < end) {
        startcode = -1;
        pos = avpriv_find_start_code(pos, end, &startcode);

        if (startcode == USER_DATA_STARTCODE && pos_p) {
            /* check if the (DivX) userdata string ends with 'p' (packed) */
            for (int i = 0; i < 255 && pos + i + 1 < end; i++) {
                if (pos[i] == 'p' && pos[i + 1] == '\0') {
                    *pos_p = pos + i - buf;
                    break;
                }
            }
        } else if (startcode == VOP_STARTCODE && nb_vop) {
            *nb_vop += 1;
            if (*nb_vop == 2 && pos_vop2) {
                *pos_vop2 = pos - buf - 4; /* subtract 4 bytes startcode */
            }
        }
    }
}