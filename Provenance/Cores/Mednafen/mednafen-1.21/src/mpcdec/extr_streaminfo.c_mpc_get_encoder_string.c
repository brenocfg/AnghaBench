#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int encoder_version; int stream_version; int /*<<< orphan*/  encoder; } ;
typedef  TYPE_1__ mpc_streaminfo ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
mpc_get_encoder_string(mpc_streaminfo* si)
{
	int ver = si->encoder_version;
	if (si->stream_version >= 8)
		ver = (si->encoder_version >> 24) * 100 + ((si->encoder_version >> 16) & 0xFF);
	if (ver <= 116) {
		if (ver == 0) {
			sprintf(si->encoder, "Buschmann 1.7.0...9, Klemm 0.90...1.05");
		} else {
			switch (ver % 10) {
				case 0:
					sprintf(si->encoder, "Release %u.%u", ver / 100,
							ver / 10 % 10);
					break;
				case 2: case 4: case 6: case 8:
					sprintf(si->encoder, "Beta %u.%02u", ver / 100,
							ver % 100);
					break;
				default:
					sprintf(si->encoder, "--Alpha-- %u.%02u",
							ver / 100, ver % 100);
					break;
			}
		}
	} else {
		int major = si->encoder_version >> 24;
		int minor = (si->encoder_version >> 16) & 0xFF;
		int build = (si->encoder_version >> 8) & 0xFF;
		char * tmp = "--Stable--";

		if (minor & 1)
			tmp = "--Unstable--";

		sprintf(si->encoder, "%s %u.%u.%u", tmp, major, minor, build);
	}
}