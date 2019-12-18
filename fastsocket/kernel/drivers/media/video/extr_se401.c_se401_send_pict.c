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
struct usb_se401 {int /*<<< orphan*/  bgain; int /*<<< orphan*/  ggain; int /*<<< orphan*/  rgain; int /*<<< orphan*/  resetlevel; int /*<<< orphan*/  expose_h; int /*<<< orphan*/  expose_m; int /*<<< orphan*/  expose_l; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV7131_REG_ABCG ; 
 int /*<<< orphan*/  HV7131_REG_AGCG ; 
 int /*<<< orphan*/  HV7131_REG_ARCG ; 
 int /*<<< orphan*/  HV7131_REG_ARLV ; 
 int /*<<< orphan*/  HV7131_REG_TITL ; 
 int /*<<< orphan*/  HV7131_REG_TITM ; 
 int /*<<< orphan*/  HV7131_REG_TITU ; 
 int /*<<< orphan*/  se401_set_feature (struct usb_se401*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int se401_send_pict(struct usb_se401 *se401)
{
	/* integration time low */
	se401_set_feature(se401, HV7131_REG_TITL, se401->expose_l);
	/* integration time mid */
	se401_set_feature(se401, HV7131_REG_TITM, se401->expose_m);
	/* integration time mid */
	se401_set_feature(se401, HV7131_REG_TITU, se401->expose_h);
	/* reset level value */
	se401_set_feature(se401, HV7131_REG_ARLV, se401->resetlevel);
	/* red color gain */
	se401_set_feature(se401, HV7131_REG_ARCG, se401->rgain);
	/* green color gain */
	se401_set_feature(se401, HV7131_REG_AGCG, se401->ggain);
	/* blue color gain */
	se401_set_feature(se401, HV7131_REG_ABCG, se401->bgain);

	return 0;
}