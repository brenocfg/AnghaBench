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
struct tlsv1_credentials {int dummy; } ;

/* Variables and functions */
 scalar_t__ os_zalloc (int) ; 

struct tlsv1_credentials * tlsv1_cred_alloc(void)
{
	struct tlsv1_credentials *cred;
	cred = (struct tlsv1_credentials *)os_zalloc(sizeof(*cred));
	return cred;
}