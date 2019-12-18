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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_phy_pub {int dummy; } ;
struct TYPE_4__ {void (* chanset ) (struct brcms_phy*,int /*<<< orphan*/ ) ;} ;
struct brcms_phy {TYPE_2__ pi_fptr; TYPE_1__* sh; } ;
struct TYPE_3__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D11_CURCHANNEL_40 ; 
 int /*<<< orphan*/  D11_CURCHANNEL_5G ; 
 int /*<<< orphan*/  M_CURCHANNEL ; 
 void stub1 (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_bmac_write_shm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wlc_phy_chanspec_set(struct brcms_phy_pub *ppi, u16 chanspec)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	u16 m_cur_channel;
	void (*chanspec_set)(struct brcms_phy *, u16) = NULL;
	m_cur_channel = CHSPEC_CHANNEL(chanspec);
	if (CHSPEC_IS5G(chanspec))
		m_cur_channel |= D11_CURCHANNEL_5G;
	if (CHSPEC_IS40(chanspec))
		m_cur_channel |= D11_CURCHANNEL_40;
	wlapi_bmac_write_shm(pi->sh->physhim, M_CURCHANNEL, m_cur_channel);

	chanspec_set = pi->pi_fptr.chanset;
	if (chanspec_set)
		(*chanspec_set)(pi, chanspec);

}