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
struct TYPE_4__ {int /*<<< orphan*/  master_ssl_key; int /*<<< orphan*/  master_ssl_cipher; int /*<<< orphan*/  master_ssl_cert; int /*<<< orphan*/  master_ssl_capath; int /*<<< orphan*/  master_ssl_ca; int /*<<< orphan*/  master_password; int /*<<< orphan*/  master_user; int /*<<< orphan*/  master_host; int /*<<< orphan*/  master_log_file; } ;
typedef  TYPE_1__ network_mysqld_masterinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void network_mysqld_masterinfo_free(network_mysqld_masterinfo_t *info) {
	if (!info) return;

	g_string_free(info->master_log_file, TRUE);
	g_string_free(info->master_host, TRUE);
	g_string_free(info->master_user, TRUE);
	g_string_free(info->master_password, TRUE);
	
	g_string_free(info->master_ssl_ca, TRUE);
	g_string_free(info->master_ssl_capath, TRUE);
	g_string_free(info->master_ssl_cert, TRUE);
	g_string_free(info->master_ssl_cipher, TRUE);
	g_string_free(info->master_ssl_key, TRUE);

	g_free(info);
}