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
struct hda_codec {int dummy; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  snd_hda_override_conn_list (struct hda_codec*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void fix_vt1802_connections(struct hda_codec *codec)
{
	static hda_nid_t conn_24[] = { 0x14, 0x1c };
	static hda_nid_t conn_33[] = { 0x1c };

	snd_hda_override_conn_list(codec, 0x24, ARRAY_SIZE(conn_24), conn_24);
	snd_hda_override_conn_list(codec, 0x33, ARRAY_SIZE(conn_33), conn_33);
}