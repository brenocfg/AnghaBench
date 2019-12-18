#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* data; } ;
typedef  TYPE_1__ br_x509_certificate ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

void
free_certificates(br_x509_certificate *certs, size_t num)
{
	size_t u;

	for (u = 0; u < num; u ++) {
		xfree(certs[u].data);
	}
	xfree(certs);
}