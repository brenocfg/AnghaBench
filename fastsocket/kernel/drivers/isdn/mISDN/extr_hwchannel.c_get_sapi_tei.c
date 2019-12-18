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
typedef  int u_int ;
typedef  int u_char ;

/* Variables and functions */

__attribute__((used)) static inline u_int
get_sapi_tei(u_char *p)
{
	u_int	sapi, tei;

	sapi = *p >> 2;
	tei = p[1] >> 1;
	return sapi | (tei << 8);
}