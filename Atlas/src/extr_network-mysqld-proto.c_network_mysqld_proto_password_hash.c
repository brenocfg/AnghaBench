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
typedef  int /*<<< orphan*/  guchar ;
typedef  int /*<<< orphan*/  gsize ;
struct TYPE_4__ {int /*<<< orphan*/  len; scalar_t__ str; int /*<<< orphan*/  allocated_len; } ;
typedef  TYPE_1__ GString ;
typedef  int /*<<< orphan*/  GChecksum ;

/* Variables and functions */
 int /*<<< orphan*/  G_CHECKSUM_SHA1 ; 
 int /*<<< orphan*/  g_checksum_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_checksum_get_digest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_checksum_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_checksum_type_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_checksum_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_set_size (TYPE_1__*,int /*<<< orphan*/ ) ; 

int network_mysqld_proto_password_hash(GString *response, const char *password, gsize password_len) {
	GChecksum *cs;

	/* first round: SHA1(password) */
	cs = g_checksum_new(G_CHECKSUM_SHA1);

	g_checksum_update(cs, (guchar *)password, password_len);

	g_string_set_size(response, g_checksum_type_get_length(G_CHECKSUM_SHA1));
	response->len = response->allocated_len; /* will be overwritten with the right value in the next step */
	g_checksum_get_digest(cs, (guchar *)response->str, &(response->len));

	g_checksum_free(cs);
	
	return 0;
}