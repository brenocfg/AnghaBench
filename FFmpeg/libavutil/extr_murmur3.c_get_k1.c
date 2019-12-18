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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RL64 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ROT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  c1 ; 
 int /*<<< orphan*/  c2 ; 

__attribute__((used)) static uint64_t inline get_k1(const uint8_t *src)
{
    uint64_t k = AV_RL64(src);
    k *= c1;
    k = ROT(k, 31);
    k *= c2;
    return k;
}