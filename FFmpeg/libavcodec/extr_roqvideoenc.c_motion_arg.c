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
struct TYPE_3__ {scalar_t__* d; } ;
typedef  TYPE_1__ motion_vect ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t motion_arg(motion_vect mot)
{
    uint8_t ax = 8 - ((uint8_t) mot.d[0]);
    uint8_t ay = 8 - ((uint8_t) mot.d[1]);
    return ((ax&15)<<4) | (ay&15);
}