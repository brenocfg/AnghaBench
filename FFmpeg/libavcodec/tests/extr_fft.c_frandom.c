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
typedef  double int16_t ;
typedef  double FFTSample ;
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 double RANGE ; 
 scalar_t__ av_lfg_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static FFTSample frandom(AVLFG *prng)
{
    return (int16_t) av_lfg_get(prng) / 32768.0 * RANGE;
}