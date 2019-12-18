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
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  G722Context ;

/* Variables and functions */
 int /*<<< orphan*/  encode_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void g722_encode_no_trellis(G722Context *c,
                                   uint8_t *dst, int nb_samples,
                                   const int16_t *samples)
{
    int i;
    for (i = 0; i < nb_samples; i += 2)
        encode_byte(c, dst++, &samples[i]);
}