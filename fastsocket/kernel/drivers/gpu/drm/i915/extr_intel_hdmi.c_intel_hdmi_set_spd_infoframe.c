#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_encoder {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sdi; int /*<<< orphan*/  pd; int /*<<< orphan*/  vn; } ;
struct TYPE_4__ {TYPE_1__ spd; } ;
struct dip_infoframe {TYPE_2__ body; int /*<<< orphan*/  len; int /*<<< orphan*/  ver; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  spd_if ;

/* Variables and functions */
 int /*<<< orphan*/  DIP_LEN_SPD ; 
 int /*<<< orphan*/  DIP_SPD_PC ; 
 int /*<<< orphan*/  DIP_TYPE_SPD ; 
 int /*<<< orphan*/  DIP_VERSION_SPD ; 
 int /*<<< orphan*/  intel_set_infoframe (struct drm_encoder*,struct dip_infoframe*) ; 
 int /*<<< orphan*/  memset (struct dip_infoframe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void intel_hdmi_set_spd_infoframe(struct drm_encoder *encoder)
{
	struct dip_infoframe spd_if;

	memset(&spd_if, 0, sizeof(spd_if));
	spd_if.type = DIP_TYPE_SPD;
	spd_if.ver = DIP_VERSION_SPD;
	spd_if.len = DIP_LEN_SPD;
	strcpy(spd_if.body.spd.vn, "Intel");
	strcpy(spd_if.body.spd.pd, "Integrated gfx");
	spd_if.body.spd.sdi = DIP_SPD_PC;

	intel_set_infoframe(encoder, &spd_if);
}