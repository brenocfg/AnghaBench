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
typedef  int /*<<< orphan*/  br_ssl_engine_context ;

/* Variables and functions */
 unsigned char* recvrec_buf (int /*<<< orphan*/  const*,size_t*) ; 

unsigned char *
br_ssl_engine_recvrec_buf(const br_ssl_engine_context *cc, size_t *len)
{
	return recvrec_buf(cc, len);
}