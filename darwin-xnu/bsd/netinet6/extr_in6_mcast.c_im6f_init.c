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
struct in6_mfilter {int* im6f_st; int /*<<< orphan*/  im6f_sources; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct in6_mfilter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline__ void
im6f_init(struct in6_mfilter *imf, const int st0, const int st1)
{
	memset(imf, 0, sizeof(struct in6_mfilter));
	RB_INIT(&imf->im6f_sources);
	imf->im6f_st[0] = st0;
	imf->im6f_st[1] = st1;
}