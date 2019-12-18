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
struct cpu_signature {int /*<<< orphan*/  pf; int /*<<< orphan*/  sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  sigmatch (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int update_match_cpu(struct cpu_signature *csig, int sig, int pf)
{
	return (!sigmatch(sig, csig->sig, pf, csig->pf)) ? 0 : 1;
}