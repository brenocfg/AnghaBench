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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int rounds; int /*<<< orphan*/ * state; int /*<<< orphan*/ * round_key; } ;
typedef  TYPE_1__ AVAES ;

/* Variables and functions */
 int /*<<< orphan*/  addkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mix (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/  subshift (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline void aes_crypt(AVAES *a, int s, const uint8_t *sbox,
                         uint32_t multbl[][256])
{
    int r;

    for (r = a->rounds - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->round_key[r]);
    }

    subshift(&a->state[0], s, sbox);
}