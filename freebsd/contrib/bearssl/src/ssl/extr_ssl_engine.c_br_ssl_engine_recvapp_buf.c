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
struct TYPE_4__ {int application_data; scalar_t__ record_type_in; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
 scalar_t__ BR_SSL_APPLICATION_DATA ; 
 unsigned char* recvpld_buf (TYPE_1__ const*,size_t*) ; 

unsigned char *
br_ssl_engine_recvapp_buf(const br_ssl_engine_context *cc, size_t *len)
{
	if (!(cc->application_data & 1)
		|| cc->record_type_in != BR_SSL_APPLICATION_DATA)
	{
		*len = 0;
		return NULL;
	}
	return recvpld_buf(cc, len);
}