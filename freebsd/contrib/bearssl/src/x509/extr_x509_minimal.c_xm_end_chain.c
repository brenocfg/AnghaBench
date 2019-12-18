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
struct TYPE_2__ {scalar_t__ err; scalar_t__ num_certs; } ;
typedef  TYPE_1__ br_x509_minimal_context ;
typedef  int /*<<< orphan*/  br_x509_class ;

/* Variables and functions */
 scalar_t__ BR_ERR_X509_EMPTY_CHAIN ; 
 scalar_t__ BR_ERR_X509_NOT_TRUSTED ; 
 scalar_t__ BR_ERR_X509_OK ; 

__attribute__((used)) static unsigned
xm_end_chain(const br_x509_class **ctx)
{
	br_x509_minimal_context *cc;

	cc = (br_x509_minimal_context *)(void *)ctx;
	if (cc->err == 0) {
		if (cc->num_certs == 0) {
			cc->err = BR_ERR_X509_EMPTY_CHAIN;
		} else {
			cc->err = BR_ERR_X509_NOT_TRUSTED;
		}
	} else if (cc->err == BR_ERR_X509_OK) {
		return 0;
	}
	return (unsigned)cc->err;
}