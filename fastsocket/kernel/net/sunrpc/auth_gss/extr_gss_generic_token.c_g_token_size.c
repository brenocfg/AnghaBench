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
struct xdr_netobj {scalar_t__ len; } ;

/* Variables and functions */
 int der_length_size (unsigned int) ; 

int
g_token_size(struct xdr_netobj *mech, unsigned int body_size)
{
	/* set body_size to sequence contents size */
	body_size += 2 + (int) mech->len;         /* NEED overflow check */
	return(1 + der_length_size(body_size) + body_size);
}