#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int suite; int req; scalar_t__ name; } ;

/* Variables and functions */
 int REQ_ECDHE_ECDSA ; 
 int REQ_ECDHE_RSA ; 
 TYPE_1__* cipher_suites ; 

int
uses_ecdhe(unsigned suite)
{
	size_t u;

	for (u = 0; cipher_suites[u].name; u ++) {
		if (cipher_suites[u].suite == suite) {
			return (cipher_suites[u].req
				& (REQ_ECDHE_RSA | REQ_ECDHE_ECDSA)) != 0;
		}
	}
	return 0;
}