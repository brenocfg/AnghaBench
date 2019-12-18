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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void samplecpy(uint8_t *dst, const uint8_t *src, int n, int maxval)
{
    if (maxval <= 255) {
        memcpy(dst, src, n);
    } else {
        int i;
        for (i=0; i<n/2; i++) {
            ((uint16_t *)dst)[i] = AV_RB16(src+2*i);
        }
    }
}