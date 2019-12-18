#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_6__* data; } ;
typedef  TYPE_1__ network_packet ;
typedef  int /*<<< orphan*/  network_mysqld_frm ;
struct TYPE_12__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
struct TYPE_11__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  GMappedFile ;
typedef  TYPE_2__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_free (TYPE_2__*) ; 
 int /*<<< orphan*/  g_mapped_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_mapped_file_get_contents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_mapped_file_get_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_mapped_file_new (char const*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  g_string_free (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * network_mysqld_frm_new () ; 
 int /*<<< orphan*/  network_mysqld_frm_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_myd_print (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ network_mysqld_proto_get_frm (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_packet_free (TYPE_1__*) ; 
 TYPE_1__* network_packet_new () ; 

int frm_dump_file(
		const char *filename,
		const char *myd_filename) {
	network_packet *packet;
	GMappedFile *f;
	GError *gerr = NULL;
	network_mysqld_frm *frm;
	int err = 0;

	f = g_mapped_file_new(filename, FALSE, &gerr);
	if (!f) {
		g_critical("%s: %s",
				G_STRLOC,
				gerr->message);
		g_error_free(gerr);
		return -1;
	}

	packet = network_packet_new();
	packet->data = g_string_new(NULL);

	packet->data->str = g_mapped_file_get_contents(f);
	packet->data->len = g_mapped_file_get_length(f);

	frm = network_mysqld_frm_new();
	err = err || network_mysqld_proto_get_frm(packet, frm);
	if (!err) {
		network_mysqld_frm_print(frm);
		network_mysqld_myd_print(frm, myd_filename);
	}

	g_mapped_file_free(f);

	g_string_free(packet->data, FALSE);
	network_packet_free(packet);

	return err ? -1 : 0;
}