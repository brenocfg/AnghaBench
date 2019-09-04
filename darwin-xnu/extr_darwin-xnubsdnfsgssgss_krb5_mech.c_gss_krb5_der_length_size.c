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

/* Variables and functions */

__attribute__((used)) static int
gss_krb5_der_length_size(int len)
{
	return
		len < (1 <<  7) ? 1 :
		len < (1 <<  8) ? 2 :
		len < (1 << 16) ? 3 :
		len < (1 << 24) ? 4 : 5;
}