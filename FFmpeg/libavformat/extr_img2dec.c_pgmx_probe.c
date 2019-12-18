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
typedef  int /*<<< orphan*/  AVProbeData ;

/* Variables and functions */
 scalar_t__ pnm_magic_check (int /*<<< orphan*/  const*,int) ; 
 int pnm_probe (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int pgmx_probe(const AVProbeData *p)
{
    return pnm_magic_check(p, 2) || pnm_magic_check(p, 5) ? pnm_probe(p) : 0;
}