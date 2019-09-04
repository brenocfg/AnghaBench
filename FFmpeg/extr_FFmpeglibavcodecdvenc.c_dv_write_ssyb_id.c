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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline int dv_write_ssyb_id(uint8_t syb_num, uint8_t fr, uint8_t *buf)
{
    if (syb_num == 0 || syb_num == 6) {
        buf[0] = (fr << 7) | /* FR ID 1 - first half of each channel; 0 - second */
                 (0  << 4) | /* AP3 (Subcode application ID) */
                 0x0f;       /* reserved -- always 1 */
    } else if (syb_num == 11) {
        buf[0] = (fr << 7) | /* FR ID 1 - first half of each channel; 0 - second */
                 0x7f;       /* reserved -- always 1 */
    } else {
        buf[0] = (fr << 7) | /* FR ID 1 - first half of each channel; 0 - second */
                 (0  << 4) | /* APT (Track application ID) */
                 0x0f;       /* reserved -- always 1 */
    }
    buf[1] = 0xf0 |            /* reserved -- always 1 */
             (syb_num & 0x0f); /* SSYB number 0 - 11   */
    buf[2] = 0xff;             /* reserved -- always 1 */
    return 3;
}