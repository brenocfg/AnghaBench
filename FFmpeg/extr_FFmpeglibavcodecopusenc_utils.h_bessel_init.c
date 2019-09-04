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
typedef  int /*<<< orphan*/  FFBesselFilter ;

/* Variables and functions */
 int bessel_reinit (int /*<<< orphan*/ *,float,float,float,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bessel_init(FFBesselFilter *s, float n, float f0, float fs,
                              int highpass)
{
    memset(s, 0, sizeof(FFBesselFilter));
    return bessel_reinit(s, n, f0, fs, highpass);
}