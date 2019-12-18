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
struct in_mfilter {int* imf_st; int /*<<< orphan*/  imf_sources; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct in_mfilter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline__ void
imf_init(struct in_mfilter *imf, const int st0, const int st1)
{
	memset(imf, 0, sizeof(struct in_mfilter));
	RB_INIT(&imf->imf_sources);
	imf->imf_st[0] = st0;
	imf->imf_st[1] = st1;
}