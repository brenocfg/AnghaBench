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
typedef  int /*<<< orphan*/  WPC_RECV_CALLBACK ;
typedef  int /*<<< orphan*/  URL_DATA ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  INTERNET_SETTING ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * HttpRequestEx3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,void*,void*,int,int*,int /*<<< orphan*/ ,char*,char*) ; 

BUF *HttpRequestEx2(URL_DATA *data, INTERNET_SETTING *setting,
				   UINT timeout_connect, UINT timeout_comm,
				   UINT *error_code, bool check_ssl_trust, char *post_data,
				   WPC_RECV_CALLBACK *recv_callback, void *recv_callback_param, void *sha1_cert_hash,
				   bool *cancel, UINT max_recv_size, char *header_name, char *header_value)
{
	return HttpRequestEx3(data, setting, timeout_connect, timeout_comm, error_code, check_ssl_trust,
		post_data, recv_callback, recv_callback_param, sha1_cert_hash, (sha1_cert_hash == NULL ? 0 : 1),
		cancel, max_recv_size, header_name, header_value);
}