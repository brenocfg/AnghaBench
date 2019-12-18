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
struct svc_rqst {scalar_t__ rq_auth_data; } ;
struct gss_svc_data {TYPE_1__* rsci; } ;
struct TYPE_2__ {char* client_name; } ;

/* Variables and functions */

char *svc_gss_principal(struct svc_rqst *rqstp)
{
	struct gss_svc_data *gd = (struct gss_svc_data *)rqstp->rq_auth_data;

	if (gd && gd->rsci)
		return gd->rsci->client_name;
	return NULL;
}